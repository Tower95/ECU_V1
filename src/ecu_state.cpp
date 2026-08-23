#include"ecu_state.hpp"

bool isTransitionAllowed(ECUState from, ECUState to){

  // Si la lectura no cambia nada entonces permanece en el mismo estado
  if(from == to){
    return true;
  }

  // Un caso por cada estado. El return de cada caso son los estados 
  // posibles a los que se puede ir desde el estado actual
  switch(from){

    case ECUState::INIT:
      // INIT solo puede pasar a SELF_TEST
      return to == ECUState::SELF_TEST;

    case ECUState::SELF_TEST:
      // Desde SELF_TEST se puede pasar a OPERATIONAL, DEGRADED o SAFE_STATE
      return to == ECUState::OPERATIONAL
          || to == ECUState::DEGRADED
          || to == ECUState::SAFE_STATE;

    case ECUState::OPERATIONAL:
      return to == ECUState::DEGRADED
          || to == ECUState::SAFE_STATE
          || to == ECUState::SHUTDOWN;

    case ECUState::DEGRADED:
      // Desde DEGRADED se puede pasar a OPERATIONAL, SAFE_STATE o SHUTDOWN
      return to == ECUState::OPERATIONAL
          || to == ECUState::SAFE_STATE
          || to == ECUState::SHUTDOWN;

    case ECUState::SAFE_STATE:
      // Desde SAFE_STATE solo se puede pasar a SHUTDOWN
      return to == ECUState::SHUTDOWN;

    case ECUState::SHUTDOWN:
      // Estado final
      return false;
  }

  return false;
}

ECUState applyTransition(ECUState current_state, ECUState requested_state){

  if(isTransitionAllowed(current_state, requested_state)){
    return requested_state;
  }

  // En caso de que la transicion pedida no se permita, se conserva el estado actual
  return current_state;
}


std::string ecuStateToText(ECUState state){

  switch(state){
    case ECUState::INIT:
      return "INIT";
    case ECUState::SELF_TEST:
      return "SELF_TEST";
    case ECUState::OPERATIONAL:
      return "OPERATIONAL";
    case ECUState::DEGRADED:
      return "DEGRADED";
    case ECUState::SAFE_STATE:
      return "SAFE_STATE";
    case ECUState::SHUTDOWN:
      return "SHUTDOWN";
  }

  return "DESCONOCIDO";
}
