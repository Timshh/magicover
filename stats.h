#pragma once

struct Stats {
  int ID;
  std::string Name;
  int Team;

  int HP;
  float HPMax;
  int Mana;
  float ManaMax;

  float Damage;
  int DamageRand;
  float DefaultDamageMult;

  int Element;
  float Status;
  int StatusRand;
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
};