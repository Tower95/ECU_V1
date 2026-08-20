#include <iostream>
#include "ecu.hpp"

void printState(ECUState state)
{
    switch (state)
    {
        case ECUState::INIT:
            std::cout << "INIT";
            break;

        case ECUState::SELF_TEST:
            std::cout << "SELF_TEST";
            break;

        case ECUState::OPERATIONAL:
            std::cout << "OPERATIONAL";
            break;

        case ECUState::DEGRADED:
            std::cout << "DEGRADED";
            break;

        case ECUState::SAFE_STATE:
            std::cout << "SAFE_STATE";
            break;

        case ECUState::SHUTDOWN:
            std::cout << "SHUTDOWN";
            break;
    }
}

int main()
{
    ECUState state = ECUState::INIT;

    std::cout << "Estado inicial: ";
    printState(state);
    std::cout << std::endl;

    // 1) INIT -> SELF_TEST
    state = updateState(
        state,
        ECUState::OPERATIONAL,
        false
    );

    std::cout << "Despues de INIT: ";
    printState(state);
    std::cout << std::endl;


    // Simulamos sensores normales
    ECUState evaluatedState = evaluateECU(
        80.0, true,
        2500, true,
        90.0, true,
        35.0, true,
        13.8, true
    );

    // 2) SELF_TEST -> OPERATIONAL
    state = updateState(
        state,
        evaluatedState,
        false
    );

    std::cout << "Despues de SELF_TEST: ";
    printState(state);
    std::cout << std::endl;


    // Simulamos una advertencia
    evaluatedState = evaluateECU(
        80.0, true,
        2500, true,
        105.0, true,
        35.0, true,
        13.8, true
    );

    // 3) OPERATIONAL -> DEGRADED
    state = updateState(
        state,
        evaluatedState,
        false
    );

    std::cout << "Con temperatura alta: ";
    printState(state);
    std::cout << std::endl;

    // Simulamos recuperacion a condiciones normales
    evaluatedState = evaluateECU(
    80.0, true,
    2500, true,
    90.0, true,
    35.0, true,
    13.8, true
    );

    state = updateState(
    state,
    evaluatedState,
    false
    );

    std::cout << "Despues de recuperar condiciones normales: ";
    printState(state);
    std::cout << std::endl;


    // Simulamos condición crítica
    evaluatedState = evaluateECU(
        80.0, true,
        2500, true,
        115.0, true,
        35.0, true,
        13.8, true
    );

    // 4) DEGRADED -> SAFE_STATE
    state = updateState(
        state,
        evaluatedState,
        false
    );

    std::cout << "Con temperatura critica: ";
    printState(state);
    std::cout << std::endl;


    // 5) Solicitud de apagado
    state = updateState(
        state,
        evaluatedState,
        true
    );

    std::cout << "Despues de solicitar apagado: ";
    printState(state);
    std::cout << std::endl;

    return 0;
}