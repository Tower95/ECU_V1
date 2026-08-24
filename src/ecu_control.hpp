#pragma once
#include<string>
#include"ecu_gateway.hpp"
#include"ecu_state.hpp"

// ============================================================
//  La ECU de Control solo debe responder si el dato que la
//  Gateway valido, debe procesarlo como normal, advertencia o falla critica?
//
//  Solo compara la Referencia Operativa, el rango fisico ya lo reviso la Gateway
// ============================================================

// "falla menor" a WARNING y "falla critica" a CRITICAL, las no validas no se evaluan
enum class ConditionLevel {
  NOT_EVALUATED,  // si la gateway no valido la señal
  NORMAL,         // dentro de la referencia operativa
  WARNING,        // advertencia / falla menor
  CRITICAL        // falla critica
};


// ------------------------------------------------------------
//  Referencias operativas por señal
//
//  La comparacion de RPM es estricta y la de temperatura inclusiva
//
//  La velocidad y acelerador no las tome en cuenta por que no tienen umbrales de operación
//
//  Sobre el voltaje no existe falla por sobretension debido a que la gateway ya las descarta
// ------------------------------------------------------------
const double TEMP_WARNING_C  = 100.0;   // grados Celsius
const double TEMP_CRITICAL_C = 110.0;

const double RPM_WARNING     = 6000.0;  // rpm
const double RPM_CRITICAL    = 7000.0;

const double VOLTAGE_WARNING_V  = 12.0; // volts
const double VOLTAGE_CRITICAL_V = 11.0;

// ------------------------------------------------------------
//  Señales invalidas: La regla es por conteo de señales invalidas, no por cada una
//    1 o 2 invalidas   -> falla menor   -> DEGRADED
//    3 o mas invalidas -> falla critica -> SAFE_STATE
// ------------------------------------------------------------
const int INVALID_COUNT_FOR_WARNING  = 1;
const int INVALID_COUNT_FOR_CRITICAL = 3;



// ------------------------------------------------------------
//  Coherencia entre señales
//
//  Tres reglas, las tres de momento producen ADVERTENCIA:
//
//    1. Velocidad mayor que cero con el motor detenido
//
//    2. Acelerador con alto porcentaje con el motor a bajas rpm
//
//    3. Temperatura en advertencia junto con voltaje en advertencia
//
//  Ninguna regla se juzga si una de sus dos señales no es confiable
// ------------------------------------------------------------
const double COHERENCE_SPEED_STOPPED_KMH  =   0.0;  // km/h
const double COHERENCE_RPM_STOPPED        =   0.0;  // rpm
const double COHERENCE_THROTTLE_HIGH_PCT  =  80.0;  // %
const double COHERENCE_RPM_IDLE           = 500.0;  // rpm

// Comparación contra referencias operativas; si la Gateway no la dio por valida devuelve NOT_EVALUATED
ConditionLevel classifyTemperature(double value_c, SignalStatus status);
ConditionLevel classifyRpm(double value_rpm, SignalStatus status);
ConditionLevel classifyVoltage(double value_v, SignalStatus status);

// Peor condicion entre señales que tienen su propio umbral
ConditionLevel worstThresholdCondition(double rpm,         SignalStatus rpm_status,
                                       double value_c,     SignalStatus temperature_status,
                                       double voltage_v,   SignalStatus voltage_status);

// conteo de invalidas 0 si es utilizable, 1 si no
int invalidSignalCount(SignalStatus status);

// Conteo de las cinco señales en un solo lugar
int totalInvalidCount(SignalStatus speed_status,
                      SignalStatus rpm_status,
                      SignalStatus temperature_status,
                      SignalStatus throttle_status,
                      SignalStatus voltage_status);

// Devuelkve la condicion del sistema en base a la cantidad de invalidas
ConditionLevel classifyInvalidCount(int invalid_count);

// Reglas de coherencia, una funcion por regla, cada una devuelve NOT_EVALUATED 
// si alguna de sus dos señales no es confiable, ADVERTENCIA si la incoherencia 
// esta presente, NORMAL si no.
ConditionLevel speedRpmCoherence(double speed_kmh,    SignalStatus speed_status,
                                 double rpm,          SignalStatus rpm_status);

ConditionLevel throttleRpmCoherence(double throttle_pct, SignalStatus throttle_status,
                                    double rpm,          SignalStatus rpm_status);

ConditionLevel temperatureVoltageCoherence(double value_c,   SignalStatus temperature_status,
                                           double voltage_v, SignalStatus voltage_status);

// Peor condicion entre las tres reglas de coherencia
ConditionLevel coherenceCondition(double speed_kmh,    SignalStatus speed_status,
                                  double rpm,          SignalStatus rpm_status,
                                  double value_c,      SignalStatus temperature_status,
                                  double throttle_pct, SignalStatus throttle_status,
                                  double voltage_v,    SignalStatus voltage_status);

// Aqui vive la prioridad de lo critico sobre la advertencia
ConditionLevel worstCondition(ConditionLevel left, ConditionLevel right);

// condicion del sistema -> estado que la ECU de control pide, pero es la maquina de 
// estados la que decide si se puede o no
ECUState requestedState(ConditionLevel level);

// Traduce a texto plano
std::string conditionLevelToText(ConditionLevel level);
