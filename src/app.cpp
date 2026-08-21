#include"app.hpp"
#include"ecu.hpp"
#include"manual_input.hpp"
#include"ecu_gateway.hpp"
#include <iostream>

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
  std::cout << "[INFO] Iniciando modo manual...\n" ;

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
  std::cout << "[GATEWAY] VELOCIDAD = " << speed_kmh << " km/h"
            << " | rango fisico [" << SPEED_MIN_KMH << ", " << SPEED_MAX_KMH << "]"
            << " -> " << signalStatusToText(speed_status)
            << std::endl;

  std::cout << "[GATEWAY] RPM = " << rpm << " rpm"
            << " | rango fisico [" << RPM_MIN << ", " << RPM_MAX << "]"
            << " -> " << signalStatusToText(rpm_status)
            << std::endl;

  std::cout << "[GATEWAY] TEMPERATURA = " << temperature_c << " C"
            << " | rango fisico [" << TEMP_MIN_C << ", " << TEMP_MAX_C << "]"
            << " -> " << signalStatusToText(temperature_status)
            << std::endl;

  std::cout << "[GATEWAY] ACELERADOR = " << throttle_pct << " %"
            << " | rango fisico [" << THROTTLE_MIN_PCT << ", " << THROTTLE_MAX_PCT << "]"
            << " -> " << signalStatusToText(throttle_status)
            << std::endl;

  std::cout << "[GATEWAY] VOLTAJE = " << voltage_v << " V"
            << " | rango fisico [" << VOLTAGE_MIN_V << ", " << VOLTAGE_MAX_V << "]"
            << " -> " << signalStatusToText(voltage_status)
            << std::endl;
}

void App::runSimulation(){
  std::cout << "[INFO] Iniciando modo simulacion...\n" ;
  // TODO
}
