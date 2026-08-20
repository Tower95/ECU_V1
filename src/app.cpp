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

void App::runManual(){
  std::cout << "[INFO] Iniciando modo manual...\n" ;

  // Uso la funcion y guardo como temperatura
  double temperature_c = getInputUserDouble("TEMPERATURA");
  // Valido la temperatura contra el rango del sensor
  SignalStatus temperature_status = validateTemperature(temperature_c);


  // Muestro el resultado de la gateway
  std::cout << "[GATEWAY] TEMPERATURA = " << temperature_c << " C"
            << " | rango [" << TEMP_MIN_C << ", " << TEMP_MAX_C << "]"
            << " -> " << signalStatusToText(temperature_status)
            << std::endl;
}

void App::runSimulation(){
  std::cout << "[INFO] Iniciando modo simulacion...\n" ;
  // TODO
}
