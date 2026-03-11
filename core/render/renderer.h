#pragma once
#include <cstdlib>
#include <iostream>
#include <windows.h>



class Renderer {
 public:
  Renderer();
  void PrintMessage(std::string text, int color = 15);
  void SetColor(int color);
};