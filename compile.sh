#!/bin/bash
g++ -o ./bin/ecu.exe \
  ./src/states.cpp \
  ./src/main.cpp  \
./src/ecu.cpp \
./src/app.cpp \
./src/manual_input.cpp \
./src/input_handler.cpp && ./bin/ecu.exe --manual

