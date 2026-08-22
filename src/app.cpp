#include"app.hpp"
#include"ecu.hpp"
#include"manual_input.hpp"
#include"ecu_gateway.hpp"
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
}

void App::runSimulation(){
  print(type_log::INFO, "Iniciando modo simulacion...");
  // TODO
}
