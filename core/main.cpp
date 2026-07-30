#include "gamemode.h"
#include <ctime>

int main() { 
	srand(time(NULL));
  Gamemode Game = Gamemode();
  Game.Gameloop();
  return 0;
}