#pragma once
#include <windows.h>

#include <cstdlib>
#include <iostream>

#include "uiController.h"
#include "core.h"

class ConsoleUI : public UIController {
 public:
  ConsoleUI();
  template <typename... Args>
  void PrintMessage(int const color = 15, Args&&... args) {
    SetColor(color);
    (std::cout << ... << args);
  }
  void Battle();
  void SetColor(int const color);
  void CleanRender();
  void Run();
  void CallAct(RenderActions const action, int ID, int params) override;

 private:
  int TakeInt(int const min, int const max);
  Core Game;
  Creature* SelectTarget();
};