#pragma once
#include<string>

enum class states {
  INIT,
  SELF_TEST,
  OPERATIONAL,
  DEGRADED,
  SAFE_STATE,
  SHUTDOWN,
  ERROR
};

states calculateNextState(states actual_state,states new_state);

std::string stateToText(states state);




