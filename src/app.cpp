#include"app.hpp"
#include"ecu.hpp"
#include <iostream>
#include"manual_input.hpp"

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
  std::cout << getInputUser("TEMPERATURA") <<std::endl;
  // TODO 
}

void App::runSimulation(){
  std::cout << "[INFO] Iniciando modo simulacion...\n" ;
  // TODO
}
