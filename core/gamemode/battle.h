#pragma once

#include "boss.h"
#include "creature.h"
#include "enemy.h"
#include "mage.h"
#include "res_manager.h"
#include "coreObserver.h"

enum class BattleActions { Regenerate, SupportSpell, Spell, PowerfulSpell };

class Battle {
 public:
  Battle(Mage* const player, ResourceManager* const manager, CoreObserver* observer);

  void CreateBoss(int const stage);
  void CreateEnemy(std::string const id = "");
  void CreateElite(std::string const id = "");

  std::vector<BattleActions> BattleGetActions();
  void BattleAct(BattleActions const action, int const choice1,
                 Creature* const target, int const choice2);

  int MaxEnemies;
  std::vector<std::string> NormalEnemies, EliteEnemies;
  std::vector<Creature*> Teammates, Enemies, StageBosses;

 private:
  CoreObserver* Observer;
  void BossCreator(std::string const id);
  void PrepareCast(int const choice);
  Mage* Player;

  ResourceManager* Manager;
};