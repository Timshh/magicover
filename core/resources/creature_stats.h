#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct CreatureStats {
  int ID;
  std::string Name;
  int Team;

  int HP;
  float HPMax;
  int Mana;
  float ManaMax;

  float Damage;
  int DamageRand;
  float DamageMult;
  float DefaultDamageMult;

  int Element;
  float Status;
  int StatusRand;
  float StatusMult;
  float DefaultStatusMult;

  float Defence;
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
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      CreatureStats, ID, Name, Team, HPMax, ManaMax, Damage, DamageRand, DefaultDamageMult,
      Element, Status, StatusRand, DefaultStatusMult, DefaultDefence, DodgeChance,
      FlameResist, FrostResist, DarkResist, PsychoResist, PoisonResist,
      DiseaseResist, MechanizationResist, StealerResist, DesiccantResist, Flame,
      Frost, Dark, Psycho, Poison, Disease, Mechanization, Stealer, Desiccant,
      SecondAtkChance, SecondChance, RingsMax)
};