#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "mapgenerator.h"

class Map{
 public:
  Map();

  void CreateMap();
  int MapAct(int const way);

 private:
  MapGenerator Generator = MapGenerator();

  MapGraph CurrentMap;
  int CurrentLocation;
};