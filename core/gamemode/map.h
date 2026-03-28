#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "mapgenerator.h"
#include "renderer.h"

class Map{
 public:
  Map(Renderer* render);
  
  MapGenerator Generator = MapGenerator();

  MapGraph CurrentMap;
  int CurrentLocation;

  Renderer* Render;

  void CreateMap();
  int MapAct();
};