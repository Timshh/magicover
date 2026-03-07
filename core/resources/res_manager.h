#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "creature_stats.h"
#include "ring_stats.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class ResourceManager {
 public:
  ResourceManager(const std::string& path);
  CreatureStats GetCreature(int id);
  RingStats GetRing(int id);
  std::vector<CreatureStats> CreatureData;
  std::vector<RingStats> RingData;
};