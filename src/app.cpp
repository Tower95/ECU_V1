#include"app.hpp"
#include"ecu.hpp"
#include"manual_input.hpp"
#include"ecu_gateway.hpp"
#include"ecu_control.hpp"
#include"ecu_state.hpp"
#include <iostream>
#include "logs.hpp"

App::App(int argc, char* argv[]){
  std::string arg =(argc > 1) ? argv[1] :"";
  mode = define_input(arg);

}

int App::run(){

  switch(mode){

    case type_input::MANUAL:
      runManual();
      return 0;

    case type_input::SIMULATION:
      runSimulation();
      return 0;

    case type_input::ERROR:
    default:
      return 1;
  }

}

// TODO PROVISIONAL: solo para demostrar la validacion de las lecturas
void App::runManual(){
  print(type_log::INFO , "Iniciando modo manual");

  // Primero se capturan los valores, despues se validan y se reportan
  double speed_kmh     = getInputUserDouble("VELOCIDAD");
  double rpm           = getInputUserDouble("RPM");
  double temperature_c = getInputUserDouble("TEMPERATURA");
  double throttle_pct  = getInputUserDouble("ACELERADOR");
  double voltage_v     = getInputUserDouble("VOLTAJE");

  SignalStatus speed_status       = validateSpeed(speed_kmh);
  SignalStatus rpm_status         = validateRpm(rpm);
  SignalStatus temperature_status = validateTemperature(temperature_c);
  SignalStatus throttle_status    = validateThrottle(throttle_pct);
  SignalStatus voltage_status     = validateVoltage(voltage_v);

  std::cout << std::endl;

  // Aplicar TRY, para no repetir el mismo codigo de validacion                                                                                                                     
  validateGateWay(signals::VELOCIDAD, speed_kmh, speed_status);
  validateGateWay(signals::RPM, rpm,rpm_status );
  validateGateWay(signals::TEMPERATURA, temperature_c,temperature_status );
  validateGateWay(signals::ACELERADOR, throttle_pct, throttle_status);
  validateGateWay(signals::VOLTAJE, voltage_v, voltage_status);


  // =====================================================================
  // INIT -> SELF_TEST -> ... de momento no lo acciona ninguna seña
  // la ECU de control entra con el estado que recibe
  ECUState boot_state    = ECUState::INIT;
  ECUState current_state = ECUState::INIT;

  // desde INIT la unica salida legal es SELF_TEST, por eso la aplico directamente
  current_state = applyTransition(boot_state, ECUState::SELF_TEST);

  // Niveles por señal,velocidad y acelerador no aparecen porque no tienen referencia operativa
  ConditionLevel rpm_level         = classifyRpm(rpm, rpm_status);
  ConditionLevel temperature_level = classifyTemperature(temperature_c, temperature_status);
  ConditionLevel voltage_level     = classifyVoltage(voltage_v, voltage_status);

  // Para determinar la condicion del sistema se evalua cada termino agregado desde la ECU de control
  ConditionLevel threshold_level = worstThresholdCondition(rpm,           rpm_status,
                                                           temperature_c, temperature_status,
                                                           voltage_v,     voltage_status);

  int            invalid_count = totalInvalidCount(speed_status,
                                                   rpm_status,
                                                   temperature_status,
                                                   throttle_status,
                                                   voltage_status);
  ConditionLevel invalid_level = classifyInvalidCount(invalid_count);

  // Reglas de oherencia: cada regla por separado
  ConditionLevel speed_rpm_level    = speedRpmCoherence(speed_kmh, speed_status, rpm, rpm_status);
  ConditionLevel throttle_rpm_level = throttleRpmCoherence(throttle_pct, throttle_status, rpm, rpm_status);
  ConditionLevel temp_voltage_level = temperatureVoltageCoherence(temperature_c, temperature_status,
                                                                  voltage_v, voltage_status);

  ConditionLevel coherence_level = coherenceCondition(speed_kmh,     speed_status,
                                                      rpm,           rpm_status,
                                                      temperature_c, temperature_status,
                                                      throttle_pct,  throttle_status,
                                                      voltage_v,     voltage_status);

  ConditionLevel system_level = worstCondition(worstCondition(threshold_level, invalid_level),
                                               coherence_level);
  ECUState       next_state   = applyTransition(current_state, requestedState(system_level));

  std::cout << std::endl;

  std::cout << "[CONTROL] RPM = " << rpm << " rpm"
            << " | referencia operativa [advertencia > " << RPM_WARNING
            << ", critica > " << RPM_CRITICAL << "]"
            << " -> " << conditionLevelToText(rpm_level)
            << std::endl;

  std::cout << "[CONTROL] TEMPERATURA = " << temperature_c << " C"
            << " | referencia operativa [advertencia >= " << TEMP_WARNING_C
            << ", critica >= " << TEMP_CRITICAL_C << "]"
            << " -> " << conditionLevelToText(temperature_level)
            << std::endl;

  std::cout << "[CONTROL] VOLTAJE = " << voltage_v << " V"
            << " | referencia operativa [advertencia < " << VOLTAGE_WARNING_V
            << ", critica < " << VOLTAGE_CRITICAL_V << "]"
            << " -> " << conditionLevelToText(voltage_level)
            << std::endl;

  std::cout << "[CONTROL] SEÑALES INVALIDAS = " << invalid_count << " de 5"
            << " | falla menor desde " << INVALID_COUNT_FOR_WARNING
            << ", falla critica desde " << INVALID_COUNT_FOR_CRITICAL
            << " -> " << conditionLevelToText(invalid_level)
            << std::endl;

  std::cout << "[CONTROL] COHERENCIA velocidad/RPM"
            << " | velocidad > " << COHERENCE_SPEED_STOPPED_KMH
            << " con RPM <= " << COHERENCE_RPM_STOPPED
            << " -> " << conditionLevelToText(speed_rpm_level)
            << std::endl;

  std::cout << "[CONTROL] COHERENCIA acelerador/RPM"
            << " | acelerador > " << COHERENCE_THROTTLE_HIGH_PCT << " %"
            << " con RPM < " << COHERENCE_RPM_IDLE
            << " -> " << conditionLevelToText(throttle_rpm_level)
            << std::endl;

  std::cout << "[CONTROL] COHERENCIA temperatura/voltaje"
            << " | temperatura >= " << TEMP_WARNING_C
            << " con voltaje < " << VOLTAGE_WARNING_V
            << " -> " << conditionLevelToText(temp_voltage_level)
            << std::endl;

  std::cout << "[CONTROL] CONDICION DEL SISTEMA -> "
            << conditionLevelToText(system_level)
            << std::endl;

  std::cout << "[CONTROL] ESTADO: " << ecuStateToText(boot_state)
            << " -> " << ecuStateToText(current_state)
            << "   (arranque)" // No lo decide ninguna señal, lo decide el arranque
            << std::endl;

  std::cout << "[CONTROL] ESTADO: " << ecuStateToText(current_state)
            << " -> " << ecuStateToText(next_state)
            << std::endl;
}

void App::runSimulation(){
  print(type_log::INFO, "Iniciando modo simulacion...");
  // TODO
}
