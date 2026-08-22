#include <iostream>
#include "ecu.hpp"
#include "ecu_gateway.hpp"
#include "states.hpp"

int main()
{
    std::cout << "\n--- PRUEBA GATEWAY + CONTROL ECU ---\n";

    double speed = 300.0;
    double rpm = 9000.0;
    double temperature = 500.0;
    double throttle = 35.0;
    double voltage = 13.8;

    SignalStatus speedStatus = validateSpeed(speed);
    SignalStatus rpmStatus = validateRpm(rpm);
    SignalStatus temperatureStatus = validateTemperature(temperature);
    SignalStatus throttleStatus = validateThrottle(throttle);
    SignalStatus voltageStatus = validateVoltage(voltage);

    std::cout << "Velocidad: "
              << signalStatusToText(speedStatus) << std::endl;

    std::cout << "RPM: "
              << signalStatusToText(rpmStatus) << std::endl;

    std::cout << "Temperatura: "
              << signalStatusToText(temperatureStatus) << std::endl;

    std::cout << "Acelerador: "
              << signalStatusToText(throttleStatus) << std::endl;

    std::cout << "Voltaje: "
              << signalStatusToText(voltageStatus) << std::endl;

    states gatewayTestState = evaluateECU(
        speed,
        speedStatus == SignalStatus::VALID,

        static_cast<int>(rpm),
        rpmStatus == SignalStatus::VALID,

        temperature,
        temperatureStatus == SignalStatus::VALID,

        throttle,
        throttleStatus == SignalStatus::VALID,

        voltage,
        voltageStatus == SignalStatus::VALID
    );

    std::cout << "Decision Control ECU: "
              << stateToText(gatewayTestState)
              << std::endl;


// Pruebas de SAFE_STATE y SHUTDOWN
states safeToSelfTest = calculateNextState(
    states::SAFE_STATE,
    states::SELF_TEST
);

std::cout << "SAFE_STATE -> SELF_TEST: "
          << stateToText(safeToSelfTest)
          << std::endl;

states safeToSafe = calculateNextState(
    states::SAFE_STATE,
    states::SAFE_STATE
);

std::cout << "SAFE_STATE -> SAFE_STATE: "
          << stateToText(safeToSafe)
          << std::endl;

states safeToShutdown = calculateNextState(
    states::SAFE_STATE,
    states::SHUTDOWN
);

std::cout << "SAFE_STATE -> SHUTDOWN: "
          << stateToText(safeToShutdown)
          << std::endl;

states shutdownLocked = calculateNextState(
    states::SHUTDOWN,
    states::OPERATIONAL
);

std::cout << "SHUTDOWN -> OPERATIONAL: "
          << stateToText(shutdownLocked)
          << std::endl;

std::cout << "\n--- PRUEBA DE FLUJO COMPLETO ---\n";

states flowState = states::INIT;

std::cout << stateToText(flowState);

flowState = calculateNextState(flowState, states::SELF_TEST);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::OPERATIONAL);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::DEGRADED);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::OPERATIONAL);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::SAFE_STATE);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::SELF_TEST);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::OPERATIONAL);
std::cout << " -> " << stateToText(flowState);

flowState = calculateNextState(flowState, states::SHUTDOWN);
std::cout << " -> " << stateToText(flowState);

std::cout << std::endl;

    return 0;
}