#pragma once
#include<string>
#include"input_handler.hpp"

class App {
  public:
    App(int argc, char* argv[]);
    int run();

  private:
    type_input mode;
    void runManual();
    void runSimulation();
};
