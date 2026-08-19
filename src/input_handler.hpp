#pragma once
#include<string>

enum class type_input{
  MANUAL,
  SIMULATION,
  ERROR
};


type_input define_input(std::string input_type);
