#pragma once
#include <windows.h>

#include <cstdlib>
#include <iostream>

#include "ui_controller.h"
#include "core.h"

class ConsoleUI : public UIController {
 public:
  ConsoleUI();
  template <typename... Args>
  void PrintMessage(const int color = 15, Args&&... args) {
    SetColor(color);
    (std::cout << ... << args);
  }
  void Battle();
  void Map();
  void Inventory();
  void Room();
  void SetColor(const int color);
  void CleanRender();
  void Run();
  void CallAct(const RenderActions action, const int ID, const int params,
               const int subparams) override;

 private:
  int TakeInt(const int min, const int max);
  Core game_;
  Creature* SelectTarget();
};