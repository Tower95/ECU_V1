#include"ecu.hpp"
#include<iostream>

states evaluateECU(
    double speed,
    bool speedValid,
    int rpm,
    bool rpmValid,
    double temperature,
    bool temperatureValid,
    double throttle,
    bool throttleValid,
    double voltage,
    bool voltageValid
) 

//Conteo de cuantas señales nos llegaron inválidas desde la Gateway
{
    int invalidCount = 0;

    if (!speedValid) {
        invalidCount++;
    }

    if (!rpmValid) {
        invalidCount++;
    }

    if (!temperatureValid) {
        invalidCount++;
    }

    if (!throttleValid) {
        invalidCount++;
    }

    if (!voltageValid) {
        invalidCount++;
    }


    // CONDICIONES CRÍTICAS "SAFE_STATE"
    // 3, 4 o 5 señales inválidas
    if (invalidCount >= 3) {
        return states::SAFE_STATE;
    }

    // Temperatura crítica
    if (temperatureValid && temperature >= 110.0) {
        return states::SAFE_STATE;
    }

    // RPM críticas
    if (rpmValid && rpm > 7000) {
        return states::SAFE_STATE;
    }

    // Voltaje crítico
    if (voltageValid && voltage < 11.0) {
        return states::SAFE_STATE;
    }

    // ADVERTENCIAS / FALLAS MENORES -> DEGRADED
    // 1 o 2 señales inválidas
    if (invalidCount >= 1) {
        return states::DEGRADED;
    }

    // Temperatura alta
    if (temperatureValid && temperature >= 100.0) {
        return states::DEGRADED;
    }

    // RPM altas
    if (rpmValid && rpm > 6000) {
        return states::DEGRADED;
    }

    // Voltaje bajo
    if (voltageValid && voltage < 12.0) {
        return states::DEGRADED;
    }

    // Acelerador alto con RPM demasiado bajas
    if (throttleValid && rpmValid &&throttle > 80.0 && rpm < 500) {
        return states::DEGRADED;
    }

    // Vehículo en movimiento con motor a 0 RPM
    if (speedValid && rpmValid &&
        speed > 0.0 && rpm == 0) {

        return states::DEGRADED;
    }


    // Bueni y si ya no existe ninguna condición anterior
    return states::OPERATIONAL;
}

void CalculateInjection(int rpm, float throttle){

float timeMS = (rpm * 0.002f) * (throttle / 100.0f);
std::cout << "[ECU] RPM: " << rpm
          << "| Throttle " << throttle << "%"
          << "-> Pulso de Inyeccion: " << timeMS << "ms\n";

}
