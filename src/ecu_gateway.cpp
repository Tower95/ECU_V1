#include"ecu_gateway.hpp"

// El parametro se pasa por valor para evitar modificación de dato
// Las cinco funciones son iguales, una funcion por senal, cada una valida su propio rango

SignalStatus validateSpeed(double value_kmh){

  if(value_kmh < SPEED_MIN_KMH || value_kmh > SPEED_MAX_KMH){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

SignalStatus validateRpm(double value_rpm){

  if(value_rpm < RPM_MIN || value_rpm > RPM_MAX){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

SignalStatus validateTemperature(double value_c){

  if(value_c < TEMP_MIN_C || value_c > TEMP_MAX_C){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

SignalStatus validateThrottle(double value_pct){

  if(value_pct < THROTTLE_MIN_PCT || value_pct > THROTTLE_MAX_PCT){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

SignalStatus validateVoltage(double value_v){

  if(value_v < VOLTAGE_MIN_V || value_v > VOLTAGE_MAX_V){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

// Un caso por cada señal registrada en el enum
std::string signalStatusToText(SignalStatus status){

  switch(status){
    case SignalStatus::VALID:
      return "VALIDA";
    case SignalStatus::OUT_OF_RANGE:
      return "FUERA DE RANGO";
    case SignalStatus::NOT_AVAILABLE:
      return "NO DISPONIBLE";
  }

  return "DESCONOCIDA";
}
