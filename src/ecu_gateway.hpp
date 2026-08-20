#pragma once
#include<string>

// Estado que la Gateway le pasa a la ECU de control
enum class SignalStatus {
  VALID,          // cae dentro del rango del sensor
  OUT_OF_RANGE,   // es legible pero fisicamente imposible
  NOT_AVAILABLE   // la lectura no llego
};


// Rango del sensor de temperatura
const double TEMP_MIN_C = -40.0;
const double TEMP_MAX_C = 150.0;

// Valida una lectura de temperatura contra su rango
SignalStatus validateTemperature(double value_c);

// Traduce el estado a texto para mostrarlo por consola
std::string signalStatusToText(SignalStatus status);
