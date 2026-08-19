#include<iostream>
#include<stdlib.h>
#include<string>
#include"ecu.hpp"

int main(){
  std::cout<< "Hola mundo" <<std::endl;
  CalculateInjection(3500, 45.0f);
  CalculateInjection(6000, 85.0f);
  return 0;
}

