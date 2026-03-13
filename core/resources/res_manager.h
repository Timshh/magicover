#pragma once

#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>
#include "creature_stats.h"
#include "ring_stats.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class ResourceManager {
 public:
  ResourceManager(const std::string& creaturepath, const std::string& ringpath);

  CreatureStats GetCreature(std::string id);
  RingStats GetRing(std::string id);

  std::map<std::string, CreatureStats> CreatureData;
  std::map<std::string, RingStats> RingData;
};