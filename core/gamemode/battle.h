#pragma once

#include "boss.h"
#include "creature.h"
#include "enemy.h"
#include "mage.h"
#include "res_manager.h"
#include "core_observer.h"

enum class BattleActions { kRegenerate, kSupportSpell, kSpell, kPowerfulSpell };

class Battle {
 public:
  Battle(Mage* const player, ResourceManager* const manager, CoreObserver* observer);

  void CreateBoss(const int stage);
  void CreateEnemy(const std::string id = "");
  void CreateElite(const std::string id = "");

  std::vector<BattleActions> BattleGetActions();
  void BattleAct(const BattleActions action, const int choice1,
                 Creature* const target, const int choice2);

  int max_enemies;
  std::vector<std::string> normal_enemies, elite_enemies;
  std::vector<Creature*> teammates, enemies, stage_bosses;

 private:
  void BossCreator(std::string const id);
  void PrepareCast(const int choice);
  CoreObserver* observer_;
  Mage* player_;
  ResourceManager* manager_;
};