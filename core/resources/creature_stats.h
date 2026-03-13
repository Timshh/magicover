#pragma once

#include <nlohmann/json.hpp>
#include <cstdlib>
#include <vector>
using json = nlohmann::json;

struct CreatureStats {
  std::string Name;
  int Team;

  int HP = 0;
  float HPMax;
  int Mana = 0;
  float ManaMax;

  float Damage;
  int DamageRand;
  float DamageMult = 1.0;
  float DefaultDamageMult;

  int Element;
  float Status;
  int StatusRand;
  float StatusMult = 1.0;
  float DefaultStatusMult;

  float Defence = 1.0;
  float DefaultDefence;
  float DodgeChance;

  float FlameResist;
  float FrostResist;
  float DarkResist;
  float PsychoResist;
  float PoisonResist;
  float DiseaseResist;
  float MechanizationResist;
  float StealerResist;
  float DesiccantResist;

  float Flame;
  float Frost;
  float Dark;
  float Psycho;
  float Poison;
  float Disease;
  float Mechanization;
  float Stealer;
  float Desiccant;

  float SecondAtkChance;
  int SecondChance;

  int RingsMax;

  int SpecAtkID;
  int SpecAtkChance;

  std::string CalmText = "";
  std::string HurtText = "";
  std::string DamagedText = "";
  std::string DeathText = "";
  std::vector<std::string> AtkTexts = {""};
  std::string Hint = "";
  
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
      CreatureStats, Name, Team, HPMax, ManaMax, Damage, DamageRand,
      DefaultDamageMult, Element, Status, StatusRand, DefaultStatusMult,
      DefaultDefence, DodgeChance, FlameResist, FrostResist, DarkResist,
      PsychoResist, PoisonResist, DiseaseResist, MechanizationResist,
      StealerResist, DesiccantResist, Flame, Frost, Dark, Psycho, Poison,
      Disease, Mechanization, Stealer, Desiccant, SecondAtkChance, SecondChance,
      RingsMax, SpecAtkID, SpecAtkChance, CalmText, HurtText, DamagedText, DeathText, AtkTexts, Hint)
};