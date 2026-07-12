#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "mapgenerator.h"
#include "consoleRenderer.h"

class Map{
 public:
  Map(ConsoleRenderer* render);

  void CreateMap();
  int MapAct();

 private:
  MapGenerator Generator = MapGenerator();

  MapGraph CurrentMap;
  int CurrentLocation;

  ConsoleRenderer* Render;
};