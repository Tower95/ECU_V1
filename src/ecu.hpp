#pragma once
#include "states.hpp"

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
);

void CalculateInjection(int rpm, float throttle);