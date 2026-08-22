#include "states.hpp"

states calculateNextState(states actual_state, states new_state)
{
    switch (actual_state)
    {
        case states::INIT:
            if (new_state == states::SELF_TEST)
            {
                return states::SELF_TEST;
            }

            return states::ERROR;


        case states::SELF_TEST:
            if (new_state == states::OPERATIONAL ||
                new_state == states::DEGRADED ||
                new_state == states::SAFE_STATE)
            {
                return new_state;
            }

            return states::ERROR;

        case states::OPERATIONAL:
          if (new_state == states::OPERATIONAL ||
              new_state == states::DEGRADED ||
              new_state == states::SAFE_STATE ||
              new_state == states::SHUTDOWN)
          {
              return new_state;
          }

            return states::ERROR;    

        case states::DEGRADED:
          if (new_state == states::OPERATIONAL ||
              new_state == states::DEGRADED ||
              new_state == states::SAFE_STATE ||
              new_state == states::SHUTDOWN)
          {
              return new_state;
          }

            return states::ERROR;
        
        case states::SAFE_STATE:
          if (new_state == states::SELF_TEST ||
              new_state == states::SAFE_STATE ||
              new_state == states::SHUTDOWN)
          {
             return new_state;
          }

          return states::ERROR;

        case states::SHUTDOWN:
            return states::SHUTDOWN;

        case states::ERROR:
            return states::ERROR;
    }

    return states::ERROR;
}


// Convierte el estado a texto para mostrarlo por consola
std::string stateToText(states state)
{
    switch (state)
    {
        case states::INIT:
            return "INIT";

        case states::SELF_TEST:
            return "SELF_TEST";

        case states::OPERATIONAL:
            return "OPERATIONAL";

        case states::DEGRADED:
            return "DEGRADED";

        case states::SAFE_STATE:
            return "SAFE_STATE";

        case states::SHUTDOWN:
            return "SHUTDOWN";

        case states::ERROR:
        default:
            return "ERROR";
    }
}