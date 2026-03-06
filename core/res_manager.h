#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "stats.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class ResourceManager {
 public:
  ResourceManager(const std::string& path);
  Stats GetData(int id);
  std::vector<Stats> Data;
};