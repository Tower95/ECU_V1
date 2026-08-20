#include<iostream>
#include"input_handler.hpp"

type_input define_input(std::string input_type){

  if(input_type == "--manual" || input_type == "--default"|| input_type == ""){

    return type_input::MANUAL;
  }else if(input_type == "--simulation" || input_type == "-s"){

    return type_input::SIMULATION;
  }else {
    std::cout << "Lo siento debe seleccionar un tipo de input permitido "<<std::endl;
    std::cout << "--manual     -> Ingresar datos manualmente" << std::endl;
    std::cout << "--simulation -> Dejar que el programa simule los sensores" <<std::endl;
    return type_input::ERROR;
  }

}
