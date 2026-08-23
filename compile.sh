#!/bin/bash

mkdir -p ./bin

g++ -Wall -Wextra -pedantic -o ./bin/ecu.exe \
./src/main.cpp \
./src/app.cpp \
./src/manual_input.cpp \
./src/input_handler.cpp \
./src/logs.cpp \
./src/ecu_gateway.cpp \
./src/ecu_control.cpp \
./src/ecu_state.cpp \
&& ./bin/ecu.exe --manual