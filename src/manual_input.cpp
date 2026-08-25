#include"manual_input.hpp"
#include<iostream>
#include<stdexcept>
#include"logs.hpp"

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
        print(type_log::ERROR, "Entrada invalida. Ingrese solo caracteres numericos. \n\n");
        //std::cout << "[ERROR] ";
        continue;
      }

      return result;

    } catch(const std::invalid_argument&){
      print(type_log::ERROR, input_str + "' no es un numero valido. Intente de nuevo. \n\n");
      //std::cout << "[ERROR] '" << input_str << "' no es un numero valido. Intente de nuevo. \n\n";

    } catch(const std::out_of_range&){
      print(type_log::ERROR,"El valor ingresado esta fuera de la capacidad de un numero double.\n\n" );
      //std::cout << "[ERROR] El valor ingresado esta fuera de la capacidad de un numero double.\n\n";
    }

  }

};

int getInputOption(){

  std::string input_str = "";
  int result = 0.0;

  while(true){

  printMenu();
  
    std::cin >> input_str;

    try{
      size_t processed_chars = 0;

      result = std::stoi(input_str, &processed_chars);

      if(processed_chars != input_str.length()){
        print(type_log::ERROR, "Entrada invalida. Ingrese solo caracteres numericos. \n\n");
        //std::cout << "[ERROR] ";
        continue;
      }
      if(result != 1 && result != 2){
        print(type_log::ERROR, "Entrada invalida. ese numero no es una opcion. \n\n");
        continue;
      }

      return result;

    } catch(const std::invalid_argument&){
      print(type_log::ERROR, input_str + "' no es un numero valido. Intente de nuevo. \n\n");
      //std::cout << "[ERROR] '" << input_str << "' no es un numero valido. Intente de nuevo. \n\n";

    } catch(const std::out_of_range&){
      print(type_log::ERROR,"El valor ingresado esta fuera de la capacidad de un numero double.\n\n" );
      //std::cout << "[ERROR] El valor ingresado esta fuera de la capacidad de un numero double.\n\n";
    }

  }

return 2;
}
