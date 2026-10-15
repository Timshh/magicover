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

  CreatureStats GetCreature(const std::string id);
  RingStats GetRing(const std::string id);

 private:
  std::map<std::string, CreatureStats> creature_data_;
  std::map<std::string, RingStats> ring_data_;
};