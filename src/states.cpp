#include "states.hpp"

states calculateNextState(states actual_state, std::string condition){
  //EXAMPLE TODO EXTRA LOGIC
  if(actual_state == states::INIT  && condition == "INIT"){

    return states::SELF_TEST;

  }

  return states::ERROR;
}

std::string stateToText(states state){
  switch(state){

    case states::INIT:
      return "INIT";
      break;
    case states::SELF_TEST:
      return "SELF_TEST";
      break;case states::OPERATIONAL:
        return "OPERATIONAL";
      break;case states::DEGRADED:
        return "DEGRADED";
      break;case states::SAFE_STATE:
        return "SAFE_STATE";
      break;case states::SHUTDOWN:
        return "SHUTDOWN";
      break;
    default:
      return "ERROR";

  }
}

