#include"manual_input.hpp"
#include<iostream>

std::string getInputUser(std::string sensor){

  std::string valor = "";

  std::cout << "Porfavor ingres el valor de " 
            << sensor 
            << std::endl;
  std::cin >> valor;
  return valor;

};