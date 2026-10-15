#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

#include "map_data.h"

class MapGenerator {
 public:
  MapGenerator();
  MapGraph GenerateMap(const int layers = 10, const int min_nodes = 2,
                       const int max_nodes = 5);
};