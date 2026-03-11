#include "res_manager.h"
#define NLOHMANN_DEFINE_TYPE_INTRUSIVE(type, member)

ResourceManager::ResourceManager(const std::string& creaturepath,
                                 const std::string& ringpath) {
  std::ifstream creaturefile(creaturepath);
  if (!creaturefile) {
    std::cout << "Data not opened\n";
    return;
  }
  json j;
  creaturefile >> j;


  std::vector<CreatureStats> v = j.get<std::vector<CreatureStats>>();
  for (CreatureStats item : j) {
    item.HP = item.HPMax;
    item.Mana = item.ManaMax;
    item.DamageMult = item.DefaultDamageMult;
    item.StatusMult = item.DefaultStatusMult;
    item.Defence = item.DefaultDefence;

    CreatureData.push_back(item);
  }
  creaturefile.close();


  std::ifstream ringfile(ringpath);
  if (!ringfile) {
    std::cout << "Data not opened\n";
    return;
  }
  ringfile >> j;
  for (const auto& item : j) {
    RingStats u{};
    if (!item.contains("Name")) {
      std::cout << "Missing key in item:\n" << item.dump(4) << std::endl;
      continue;
    }

    u.ID = item.at("ID").get<int>();
    u.Name = item.at("Name").get<std::string>();
    u.Description = item.at("Description").get<std::string>();
    if (!item.at("AEffects").is_null()) {
      if (item.at("AEffects").is_array()) {
        u.AEffects = item.at("AEffects").get<std::vector<int>>();
        u.AStats = item.at("AStats").get<std::vector<float>>();
      } else {
        u.AEffects.push_back(item.at("AEffects").get<int>());
        u.AStats.push_back(item.at("AStats").get<float>());
      }
    }
    if (!item.at("PEffects").is_null()) {
      if (item.at("PEffects").is_array()) {
        u.PEffects = item.at("PEffects").get<std::vector<int>>();
        u.PStats = item.at("PStats").get<std::vector<float>>();
      } else {
        u.PEffects.push_back(item.at("PEffects").get<int>());
        u.PStats.push_back(item.at("PStats").get<float>());
      }
    }

    RingData.push_back(u);
  }
  ringfile.close();
}

CreatureStats ResourceManager::GetCreature(int id) {
  for (int i = 0; i < CreatureData.size(); i++) {
    if (CreatureData[i].ID == id) {
      return CreatureData[i];
    }
  }
  return CreatureData[0];
  std::cout << "Error" << std::endl;
}

RingStats ResourceManager::GetRing(int id) {
  for (int i = 0; i < RingData.size(); i++) {
    if (RingData[i].ID == id) {
      return RingData[i];
    }
  }
  return RingData[0];
  std::cout << "Error" << std::endl;
}
