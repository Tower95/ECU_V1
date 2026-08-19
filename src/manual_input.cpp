#include"manual_input.hpp"
#include<iostream>
#include<stdexcept>

double getInputUserDouble(std::string sensor_name){

  std::string input_str = "";
  double result = 0.0;

  while(true){

    std::cout << "Porfavor ingres el valor de " 
      << sensor_name 
      << ":";

    std::cin >> input_str;

    try{
      size_t processed_chars = 0;

      result = std::stod(input_str, &processed_chars);

      if(processed_chars != input_str.length()){
        std::cout << "[ERROR] Entrada invalida. Ingrese solo caracteres numericos. \n\n";
        continue;
      }

      return result;

    } catch(const std::invalid_argument&){
      std::cout << "[ERROR] '" << input_str << "' no es un numero valido. Intente de nuevo. \n\n";

    } catch(const std::out_of_range&){
      std::cout << "[ERROR] El valor ingresado esta fuera de la capacidad de un numero double.\n\n";
    }

  }

};

