#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

#include "mapData.h"

class MapGenerator {
 public:
  MapGenerator();
  MapGraph GenerateMap(int layers = 10, int minnodes = 2, int maxnodes = 5);
};