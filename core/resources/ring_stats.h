#pragma once

struct RingStats {
  bool uneqippable = true, equipped = false;

  std::string name, description;

  std::vector<int> passive_effects;
  std::vector<float> passive_stats;
  std::vector<int> active_effects;
  std::vector<float> active_stats;
};