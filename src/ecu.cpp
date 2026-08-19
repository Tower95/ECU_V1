#include"ecu.hpp"
#include<iostream>

void CalculateInjection(int rpm, float throttle){

float timeMS = (rpm * 0.002f) * (throttle / 100.0f);
std::cout << "[ECU] RPM: " << rpm
          << "| Throttle " << throttle << "%"
          << "-> Pulso de Inyeccion: " << timeMS << "ms\n";

}
