#include "res_manager.h"
#define NLOHMANN_DEFINE_TYPE_INTRUSIVE(type, member)

ResourceManager::ResourceManager(const std::string& creature_path,
                                 const std::string& ring_path) {
  std::ifstream creature_file(creature_path);
  if (!creature_file) {
    std::cout << "Data not opened\n";
    return;
  }
  json j;
  creature_file >> j;

  std::vector<CreatureStats> v = j.get<std::vector<CreatureStats>>();
  for (CreatureStats item : j) {
    item.hp = item.hp_max;
    item.mana = item.mana_max;
    item.damage_mult = item.default_damage_mult;
    item.status_mult = item.default_status_mult;
    item.defence = item.default_defence;

    creature_data_.insert({item.name, item});
  }
  creature_file.close();

  std::ifstream ringfile(ring_path);
  if (!ringfile) {
    std::cout << "Data not opened\n";
    return;
  }
  ringfile >> j;
  for (const auto& item : j) {
    RingStats u{};
    if (!item.contains("name")) {
      std::cout << "Missing key in item:\n" << item.dump(4) << std::endl;
      continue;
    }
    u.name = item.at("name").get<std::string>();
    u.description = item.at("description").get<std::string>();
    if (!item.at("active_effects").is_null()) {
      if (item.at("active_effects").is_array()) {
        u.active_effects = item.at("active_effects").get<std::vector<int>>();
        u.active_stats = item.at("active_stats").get<std::vector<float>>();
      } else {
        u.active_effects.push_back(item.at("active_effects").get<int>());
        u.active_stats.push_back(item.at("active_stats").get<float>());
      }
    }
    if (!item.at("passive_effects").is_null()) {
      if (item.at("passive_effects").is_array()) {
        u.passive_effects = item.at("passive_effects").get<std::vector<int>>();
        u.passive_stats = item.at("passive_stats").get<std::vector<float>>();
      } else {
        u.passive_effects.push_back(item.at("passive_effects").get<int>());
        u.passive_stats.push_back(item.at("passive_stats").get<float>());
      }
    }
    ring_data_.insert({u.name, u});
  }
  ringfile.close();
}

CreatureStats ResourceManager::GetCreature(const std::string id) {
  if (creature_data_.contains(id)) {
    return creature_data_.at(id);
  }
  std::cout << "Creature not found error: " << id << std::endl;
  return creature_data_.at("Patient zero");
}

RingStats ResourceManager::GetRing(const std::string id) {
  if (ring_data_.contains(id)) {
    return ring_data_.at(id);
  }
  std::cout << "Ring not found error" << std::endl;
  return ring_data_.at("Blue Blood ring");
}
