#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "map_generator.h"

class Map{
 public:
  Map();

  void CreateMap();
  int MapAct(const int way);
  int GetNodeType(const int id);
  std::vector<int> GetWays();

 private:
  MapGenerator generator_ = MapGenerator();

  MapGraph current_map_;
  int current_location_;
};