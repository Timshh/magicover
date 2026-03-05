#include "res_manager.h"

ResourceManager::ResourceManager(const std::string& path) {
  std::ifstream file("external/data.json");
  if (!file) {
    std::cout << "Data not opened\n";
    return;
  }
  json j;
  file >> j;
  for (const auto& item : j) {
    Stats u{};
    if (!item.contains("Name")) {
      std::cout << "Missing key in item:\n" << item.dump(4) << std::endl;
      continue;
    }

    u.ID = item.at("ID").get<int>();
    u.Name = item.at("Name").get<std::string>();
    u.Team = item.at("Team").get<int>();

    u.HPMax = item.at("HPMax").get<float>();
    u.HP = u.HPMax;
    u.ManaMax = item.at("ManaMax").get<float>();
    u.Mana = u.ManaMax;

    u.Damage = item.at("Damage").get<float>();
    u.DamageRand = item.at("DamageRand").get<int>();
    u.DefaultDamageMult = item.at("DefaultDamageMult").get<float>();

    u.Element = item.at("Element").get<int>();
    u.Status = item.at("Status").get<float>();
    u.StatusRand = item.at("StatusRand").get<int>();
    u.DefaultStatusMult = item.at("DefaultStatusMult").get<float>();

    u.Defence = item.at("Defence").get<float>();
    u.DefaultDefence = item.at("DefaultDefence").get<float>();
    u.DodgeChance = item.at("DodgeChance").get<float>();

    u.FlameResist = item.at("FlameResist").get<float>();
    u.FrostResist = item.at("FrostResist").get<float>();
    u.DarkResist = item.at("DarkResist").get<float>();
    u.PsychoResist = item.at("PsychoResist").get<float>();
    u.PoisonResist = item.at("PoisonResist").get<float>();
    u.DiseaseResist = item.at("DiseaseResist").get<float>();
    u.MechanizationResist = item.at("MechanizationResist").get<float>();
    u.StealerResist = item.at("StealerResist").get<float>();
    u.DesiccantResist = item.at("DesiccantResist").get<float>();

    u.Flame = item.at("Flame").get<float>();
    u.Frost = item.at("Frost").get<float>();
    u.Dark = item.at("Dark").get<float>();
    u.Psycho = item.at("Psycho").get<float>();
    u.Poison = item.at("Poison").get<float>();
    u.Disease = item.at("Disease").get<float>();
    u.Mechanization = item.at("Mechanization").get<float>();
    u.Stealer = item.at("Stealer").get<float>();
    u.Desiccant = item.at("Desiccant").get<float>();

    u.SecondAtkChance = item.at("SecondAtkChance").get<float>();
    u.SecondChance = item.at("SecondChance").get<int>();

    u.RingsMax = item.at("RingsMax").get<int>();

    Data.push_back(u);
  }
  file.close();
}

Stats ResourceManager::GetData(int id) {
  for (int i = 0; i < Data.size(); i++) {
    if (Data[i].ID == id) {
      return Data[i];
    }
  }
  return Data[0];
  std::cout << "Error" << std::endl;
}
