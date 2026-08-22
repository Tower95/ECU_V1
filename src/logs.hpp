#pragma once
#include<string>
#include<iomanip>
#include"ecu_gateway.hpp"

using std::string;

enum class type_log { 
  INFO,
  WARNING,
  CONTROL,
  GATWAY,
  ERROR
};

enum class signals{
  VELOCIDAD,
  RPM,
  TEMPERATURA,
  ACELERADOR,
  VOLTAJE
};

void print(type_log type, string text);

void validateGateWay(signals signal,double value, SignalStatus status); 

string controReport();


