#pragma once

enum class ECUState {
    INIT,
    SELF_TEST,
    OPERATIONAL,
    DEGRADED,
    SAFE_STATE,
    SHUTDOWN
};

ECUState evaluateECU(
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

void CalculateInjection (int rpm, float throttle);

