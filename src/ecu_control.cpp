#include"ecu_control.hpp"

// Los parametros se pasan por valor, al igual que la gateway no modifica solo compara

ConditionLevel classifyTemperature(double value_c, SignalStatus status){

  // Primero reviso el status que determinó la gateway, una señal invalida no se compara
  // Devuelve NOT_EVALUATED,
  if(status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  // Priorizo verificar el status critico
  if(value_c >= TEMP_CRITICAL_C){
    return ConditionLevel::CRITICAL;
  }

  if(value_c >= TEMP_WARNING_C){
    return ConditionLevel::WARNING;
  }

  // Si no es necesario reportar advertencia ni falla critica, es normal
  return ConditionLevel::NORMAL;
}

ConditionLevel classifyRpm(double value_rpm, SignalStatus status){

  if(status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  if(value_rpm > RPM_CRITICAL){
    return ConditionLevel::CRITICAL;
  }

  if(value_rpm > RPM_WARNING){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

ConditionLevel classifyVoltage(double value_v, SignalStatus status){

  if(status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  if(value_v < VOLTAGE_CRITICAL_V){
    return ConditionLevel::CRITICAL;
  }

  if(value_v < VOLTAGE_WARNING_V){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

// Las tres señales con umbral propio se agregan aca para agrefgar o quitar facilmente
ConditionLevel worstThresholdCondition(double rpm,       SignalStatus rpm_status,
                                       double value_c,   SignalStatus temperature_status,
                                       double voltage_v, SignalStatus voltage_status){

  ConditionLevel rpm_level         = classifyRpm(rpm, rpm_status);
  ConditionLevel temperature_level = classifyTemperature(value_c, temperature_status);
  ConditionLevel voltage_level     = classifyVoltage(voltage_v, voltage_status);

  return worstCondition(worstCondition(rpm_level, temperature_level), voltage_level);
}

int invalidSignalCount(SignalStatus status){

  // Siempre que una señal no sea valida se retorna 1 para que se sume al conteo de invalidas
  if(status != SignalStatus::VALID){
    return 1;
  }

  return 0;
}

// Las cinco señales se cuentan aca
int totalInvalidCount(SignalStatus speed_status,
                      SignalStatus rpm_status,
                      SignalStatus temperature_status,
                      SignalStatus throttle_status,
                      SignalStatus voltage_status){

  return invalidSignalCount(speed_status)
       + invalidSignalCount(rpm_status)
       + invalidSignalCount(temperature_status)
       + invalidSignalCount(throttle_status)
       + invalidSignalCount(voltage_status);
}

ConditionLevel classifyInvalidCount(int invalid_count){

  if(invalid_count >= INVALID_COUNT_FOR_CRITICAL){
    return ConditionLevel::CRITICAL;
  }

  if(invalid_count >= INVALID_COUNT_FOR_WARNING){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

// ------------------------------------------------------------
//  Coherencia entre señales
//
//  Si una de las dos señales no es confiable, no hay con que comparar
// ------------------------------------------------------------

ConditionLevel speedRpmCoherence(double speed_kmh, SignalStatus speed_status,
                                 double rpm,       SignalStatus rpm_status){

  if(speed_status != SignalStatus::VALID || rpm_status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  if(speed_kmh > COHERENCE_SPEED_STOPPED_KMH && rpm <= COHERENCE_RPM_STOPPED){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

ConditionLevel throttleRpmCoherence(double throttle_pct, SignalStatus throttle_status,
                                    double rpm,          SignalStatus rpm_status){

  if(throttle_status != SignalStatus::VALID || rpm_status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  if(throttle_pct > COHERENCE_THROTTLE_HIGH_PCT && rpm < COHERENCE_RPM_IDLE){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

ConditionLevel temperatureVoltageCoherence(double value_c,   SignalStatus temperature_status,
                                           double voltage_v, SignalStatus voltage_status){

  if(temperature_status != SignalStatus::VALID || voltage_status != SignalStatus::VALID){
    return ConditionLevel::NOT_EVALUATED;
  }

  if(value_c >= TEMP_WARNING_C && voltage_v < VOLTAGE_WARNING_V){
    return ConditionLevel::WARNING;
  }

  return ConditionLevel::NORMAL;
}

ConditionLevel coherenceCondition(double speed_kmh,    SignalStatus speed_status,
                                  double rpm,          SignalStatus rpm_status,
                                  double value_c,      SignalStatus temperature_status,
                                  double throttle_pct, SignalStatus throttle_status,
                                  double voltage_v,    SignalStatus voltage_status){

  ConditionLevel speed_rpm    = speedRpmCoherence(speed_kmh, speed_status, rpm, rpm_status);
  ConditionLevel throttle_rpm = throttleRpmCoherence(throttle_pct, throttle_status, rpm, rpm_status);
  ConditionLevel temp_voltage = temperatureVoltageCoherence(value_c, temperature_status,
                                                            voltage_v, voltage_status);

  return worstCondition(worstCondition(speed_rpm, throttle_rpm), temp_voltage);
}

// Nuevamente priorizo lo critico sobre la advertencia
ConditionLevel worstCondition(ConditionLevel left, ConditionLevel right){

  if(left == ConditionLevel::CRITICAL || right == ConditionLevel::CRITICAL){
    return ConditionLevel::CRITICAL;
  }

  if(left == ConditionLevel::WARNING || right == ConditionLevel::WARNING){
    return ConditionLevel::WARNING;
  }

  // NOT_EVALUATED es neutro
  if(left == ConditionLevel::NORMAL || right == ConditionLevel::NORMAL){
    return ConditionLevel::NORMAL;
  }

  return ConditionLevel::NOT_EVALUATED;
}

ECUState requestedState(ConditionLevel level){

  switch(level){
    case ConditionLevel::CRITICAL:
      return ECUState::SAFE_STATE;
    case ConditionLevel::WARNING:
      return ECUState::DEGRADED;
    case ConditionLevel::NORMAL:
      return ECUState::OPERATIONAL;
    case ConditionLevel::NOT_EVALUATED:
      // Por construccion no puede llegar
      return ECUState::SAFE_STATE;
  }

  return ECUState::SAFE_STATE;
}

std::string conditionLevelToText(ConditionLevel level){

  switch(level){
    case ConditionLevel::NOT_EVALUATED:
      return "NO EVALUADA (lectura no utilizable)";
    case ConditionLevel::NORMAL:
      return "NORMAL";
    case ConditionLevel::WARNING:
      return "ADVERTENCIA";
    case ConditionLevel::CRITICAL:
      return "CRITICA";
  }

  return "DESCONOCIDA";
}
