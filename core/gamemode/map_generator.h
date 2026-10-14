#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

#include "map_data.h"

class MapGenerator {
 public:
  MapGenerator();
  MapGraph GenerateMap(int layers = 10, int minnodes = 2, int maxnodes = 5);
};