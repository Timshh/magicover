#pragma once
#include <cstdlib>
#include <iostream>
#include <windows.h>



class Renderer {
 public:
  Renderer();
  template <typename... Args>
  void PrintMessage(int color = 15, Args&&... args) {
    SetColor(color);
    (std::cout << ... << args);
  }
  void SetColor(int color);
  void CleanRender();
};