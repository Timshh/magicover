#pragma once

struct RingStats {
  bool Uneqippable = true, Equipped = false;

  std::string Name, Description;

  std::vector<int> PEffects;
  std::vector<float> PStats;
  std::vector<int> AEffects;
  std::vector<float> AStats;
};