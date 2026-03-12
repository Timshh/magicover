#include "renderer.h"

Renderer::Renderer() {}

void Renderer::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void Renderer::CleanRender() { system("cls"); }