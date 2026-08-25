#include <iostream>
#include "logs.hpp"

void print(type_log type, string text){

  string log = "";
  switch(type){

    case type_log::INFO:

      std::cout << "[INFO] " << text << std::endl ;

      break;
    case type_log::WARNING:

      std::cout << "[WARNING] " << text << std::endl ;
      break;
    case type_log::CONTROL:

      std::cout << "[CONTROL] " << text << std::endl ;
      break;
    case type_log::GATWAY:

      std::cout << "[GATWAY] " << text << std::endl ;
      break;
    case type_log::ERROR:

      std::cout << "[ERROR] " << text << std::endl ;
      break;
  }


}
void validateGateWay(signals signal,double value, SignalStatus status){

  switch(signal){
    case signals::VELOCIDAD:
      std::cout << "[GATEWAY] VELOCIDAD = " << value << " km/h"
        << " | rango fisico [" << SPEED_MIN_KMH << ", " << SPEED_MAX_KMH << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::RPM:
      std::cout << "[GATEWAY] RPM = " << value << " rpm"
        << " | rango fisico [" << RPM_MIN << ", " << RPM_MAX << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::TEMPERATURA:
      std::cout << "[GATEWAY] TEMPERATURA = " << value << " C"
        << " | rango fisico [" << TEMP_MIN_C << ", " << TEMP_MAX_C << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::ACELERADOR:
      std::cout << "[GATEWAY] ACELERADOR = " << value << " %"
        << " | rango fisico [" << THROTTLE_MIN_PCT << ", " << THROTTLE_MAX_PCT << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;  

    case signals::VOLTAJE:
      std::cout << "[GATEWAY] VOLTAJE = " << value << " V"
        << " | rango fisico [" << VOLTAGE_MIN_V << ", " << VOLTAGE_MAX_V << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;
  }

}
void controlOperative(signals signal,double value, SignalStatus status){

  switch(signal){
    case signals::VELOCIDAD:
      std::cout << "[GATEWAY] VELOCIDAD = " << value << " km/h"
        << " | rango fisico [" << SPEED_MIN_KMH << ", " << SPEED_MAX_KMH << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::RPM:
      std::cout << "[GATEWAY] RPM = " << value << " rpm"
        << " | rango fisico [" << RPM_MIN << ", " << RPM_MAX << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::TEMPERATURA:
      std::cout << "[GATEWAY] TEMPERATURA = " << value << " C"
        << " | rango fisico [" << TEMP_MIN_C << ", " << TEMP_MAX_C << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;

    case signals::ACELERADOR:
      std::cout << "[GATEWAY] ACELERADOR = " << value << " %"
        << " | rango fisico [" << THROTTLE_MIN_PCT << ", " << THROTTLE_MAX_PCT << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;  

    case signals::VOLTAJE:
      std::cout << "[GATEWAY] VOLTAJE = " << value << " V"
        << " | rango fisico [" << VOLTAGE_MIN_V << ", " << VOLTAGE_MAX_V << "]"
        << " -> " << signalStatusToText(status)
        << std::endl;
      break;
  }

}

void printMenu(){
 std::cout << "***************MENU***************" << std::endl;
 std::cout <<"1.- Ingresar datos" << std::endl;
 std::cout <<"2.- Salir" << std::endl;
 std::cout <<"Ingrese una opcion: " << std::endl;
}