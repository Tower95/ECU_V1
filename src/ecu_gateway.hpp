#pragma once
#include<string>

// ============================================================
//  La gateway solo debe responder una sola pregunta, el dato leido, es confiable?
//
//  Solo comparar contra el rango fisico del sensor, decidir si el valor indica
//  condicion normal, advertencia o critica es tarea de la ECU de control.
// ============================================================

// Estado que la Gateway le pasa a la ECU de control
enum class SignalStatus {
  VALID,          // cae dentro del rango fisico del sensor
  OUT_OF_RANGE,   // es legible pero fisicamente imposible
  NOT_AVAILABLE   // la lectura no llego
};

// Nota sobre NOT_AVAILABLE:
// Aunque aun no se implementa, la Gateway deberia poder reportar que un sensor no esta disponible(tal como se solicita en la documentación)
// Por eso desde ahora ya la incluyo en el enum

// Rangos fisicos de los cinco sensores
const double SPEED_MIN_KMH    =    0.0;   // km/h
const double SPEED_MAX_KMH    =  250.0;

const double RPM_MIN          =    0.0;   // rpm
const double RPM_MAX          = 8000.0;

const double TEMP_MIN_C       =  -40.0;   // grados Celsius
const double TEMP_MAX_C       =  150.0;

const double THROTTLE_MIN_PCT =    0.0;   // porcentaje
const double THROTTLE_MAX_PCT =  100.0;

const double VOLTAGE_MIN_V    =    9.0;   // volts
const double VOLTAGE_MAX_V    =   16.0;

// Se valida cada lectura contra su rango fisico y devuelve el estado de la señal
// La funcion getInputUserDouble() siempre debe garantizar que el valor es numerico
SignalStatus validateSpeed(double value_kmh);
SignalStatus validateRpm(double value_rpm);
SignalStatus validateTemperature(double value_c);
SignalStatus validateThrottle(double value_pct);
SignalStatus validateVoltage(double value_v);

// Traduce el estado a texto plano
std::string signalStatusToText(SignalStatus status);
