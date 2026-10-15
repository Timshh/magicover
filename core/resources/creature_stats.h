#pragma once

#include <cstdlib>
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

struct CreatureStats {
  std::string name;
  int team;

  int hp = 0;
  float hp_max;
  int mana = 0;
  float mana_max;

  float damage;
  int damage_rand;
  float damage_mult = 1.0;
  float default_damage_mult;

  int element;
  float status;
  int status_rand;
  float status_mult = 1.0;
  float default_status_mult;

  float defence = 1.0;
  float default_defence;
  float dodge_chance;

  float flame_resist;
  float frost_resist;
  float dark_resist;
  float psycho_resist;
  float poison_resist;
  float disease_resist;
  float mechanization_resist;
  float stealer_resist;
  float desiccant_resist;

  float flame;
  float frost;
  float dark;
  float psycho;
  float poison;
  float disease;
  float mechanization;
  float stealer;
  float desiccant;

  float second_atk_chance;
  int second_chance;

  int rings_max;

  int spec_atk_id;
  int spec_atk_chance;

  std::string calm_text = "";
  std::string hurt_text = "";
  std::string damaged_text = "";
  std::string death_text = "";
  std::vector<std::string> atk_texts = {""};
  std::string hint = "";

  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
      CreatureStats, name, team, hp_max, mana_max, damage, damage_rand,
      default_damage_mult, element, status, status_rand, default_status_mult,
      default_defence, dodge_chance, flame_resist, frost_resist, dark_resist,
      psycho_resist, poison_resist, disease_resist, mechanization_resist,
      stealer_resist, desiccant_resist, flame, frost, dark, psycho, poison,
      disease, mechanization, stealer, desiccant, second_atk_chance, second_chance,
      rings_max, spec_atk_id, spec_atk_chance, calm_text, hurt_text, damaged_text,
      death_text, atk_texts, hint)
};