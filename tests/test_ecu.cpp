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
    ECUState state = evaluateECU(
        80.0, false,     // velocidad
        2500, true,     // RPM
        115, true,     // temperatura
        35.0, true,     // acelerador
        13.8, true      // voltaje
    );

    std::cout << "Estado de la ECU: ";
    printState(state);
    std::cout << std::endl;

    return 0;
}