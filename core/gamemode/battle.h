#pragma once

#include "boss.h"
#include "consoleRenderer.h"
#include "creature.h"
#include "enemy.h"
#include "mage.h"
#include "res_manager.h"

class Battle {
 public:
  Battle(ConsoleRenderer* globalRender, Renderer* render,
         std::vector<Creature*>* const teammates,
         std::vector<Creature*>* const enemies,
         std::vector<Creature*>* const stageBosses,
         Mage* player, int* const stage,
         int* const maxEnemies, ResourceManager* const manager);

  void CreateBoss();
  void EnemyChooser();
  bool StartBattle();

 private:
  Mage* Player;
  ConsoleRenderer* GlobalRender;
  Renderer* Render;
  Creature* Target = nullptr;

  int *Stage, *MaxEnemies;

  std::vector<Creature*>*Teammates, *Enemies, *StageBosses;
  ResourceManager* Manager;
};