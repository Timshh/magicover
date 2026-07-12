#include "consoleRenderer.h"

ConsoleRenderer::ConsoleRenderer() {}

void ConsoleRenderer::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void ConsoleRenderer::CleanRender() { system("cls"); }