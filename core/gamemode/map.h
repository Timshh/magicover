#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "mapgenerator.h"
#include "consoleRenderer.h"

class Map{
 public:
  Map(ConsoleRenderer* render);
  
  MapGenerator Generator = MapGenerator();

  MapGraph CurrentMap;
  int CurrentLocation;

  ConsoleRenderer* Render;

  void CreateMap();
  int MapAct();
};