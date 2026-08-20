#include"ecu_gateway.hpp"

// La temperatura se pasa por valor
SignalStatus validateTemperature(double value_c){

  if(value_c < TEMP_MIN_C || value_c > TEMP_MAX_C){
    return SignalStatus::OUT_OF_RANGE;
  }

  return SignalStatus::VALID;
}

// Simplemente para traducir el estato a texto
std::string signalStatusToText(SignalStatus status){

  switch(status){
    case SignalStatus::VALID:
      return "VALIDA";
    case SignalStatus::OUT_OF_RANGE:
      return "FUERA DE RANGO";
    case SignalStatus::NOT_AVAILABLE:
      return "NO DISPONIBLE";
  }

  return "DESCONOCIDA";
}
