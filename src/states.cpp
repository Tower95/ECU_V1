#include "states.hpp"

states calculateNextState(states actual_state, states new_state){
  //EXAMPLE TODO EXTRA LOGIC
  //
  switch(actual_state){
    case states::INIT:

      if(new_state == states::SELF_TEST ){

        return states::SELF_TEST;

      }else{


      }
      break;
    case states::SELF_TEST:
      
      if(new_state
      break;
  }

  return states::ERROR;
}

//Function to parse states into String
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

