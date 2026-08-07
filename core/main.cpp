#include <ctime>

#include "consoleUI.h"
#include "core.h"

int main() {
  srand(time(NULL));
  ConsoleUI UI;
  UI.Run();
  return 0;
}