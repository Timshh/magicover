#pragma once

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "creature_stats.h"
#include "nlohmann/json.hpp"
#include "ring_stats.h"

using json = nlohmann::json;

class ResourceManager {
 public:
  ResourceManager(const std::string& creature_path, const std::string& ring_path);

  CreatureStats GetCreature(const std::string id);
  RingStats GetRing(const std::string id);

 private:
  std::map<std::string, CreatureStats> creature_data_;
  std::map<std::string, RingStats> ring_data_;
};