#include <ctime>

#include "console_ui.h"
#include "core.h"

int main() {
  srand(time(NULL));
  ConsoleUI ui;
  ui.Run();
  return 0;
}