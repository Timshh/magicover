#include "battle.h"

Battle::Battle(Mage* const player, ResourceManager* const manager,
               CoreObserver* observer)
    : teammates({player}),
      enemies(),
      stage_bosses(),
      player_(player),
      max_enemies(5),
      manager_(manager),
      observer_(observer) {}

void Battle::CreateBoss(const int stage) {
  switch (stage) {
    case 0:
      BossCreator("Shield guardian");

      BossCreator("Axe guardian");
      break;
    case 1:
      BossCreator("InfArmY");
      break;
    case 2:
      BossCreator("GO-13M");
      break;
    case 3:
      BossCreator("Wings");
      BossCreator("Tyrant");
      BossCreator("Halo");
      break;
  }
}

void Battle::CreateEnemy(const std::string id) {
  std::string index = id;
  if (id == "") {
    index = normal_enemies[rand() % normal_enemies.size()];
  }
  enemies.push_back(new Enemy(manager_->GetCreature(index), &enemies, observer_,
                              enemies.size()));
}

void Battle::CreateElite(const std::string id) {
  std::string index = id;
  if (id == "") {
    index = elite_enemies[rand() % elite_enemies.size()];
  }
  enemies.push_back(new Enemy(manager_->GetCreature(index), &enemies, observer_,
                              enemies.size()));
}

std::vector<BattleActions> Battle::BattleGetActions() {
  std::vector<BattleActions> result = {{BattleActions::Regenerate}};
  if (player_->params.mana >= 20) {
    result.push_back(BattleActions::SupportSpell);
    result.push_back(BattleActions::Spell);
    if (player_->params.mana >= 40) {
      result.push_back(BattleActions::PowerfulSpell);
    }
  }
  return result;
}

void Battle::BossCreator(const std::string id) {
  stage_bosses.push_back(new Boss(manager_->GetCreature(id), &stage_bosses,
                                 &enemies, &max_enemies, manager_, observer_,
                                 stage_bosses.size() + 10000));
  observer_->CallAct(RenderActions::kAppear, stage_bosses.size() + 9999);
}

void Battle::PrepareCast(const int choice) {
  switch (choice) {
    case 1:
      player_->params.damage = 20;
      player_->params.status = 5;
      player_->params.element = 1;
      break;
    case 2:
      player_->params.damage = 25;
      player_->params.status = 3.5;
      player_->params.element = 2;
      break;
    case 3:
      player_->params.damage = 15;
      player_->params.status = 7.5;
      player_->params.element = 3;
      break;
    case 4:
      player_->params.damage = 10;
      player_->params.status = 9;
      player_->params.element = 4;
      break;
  }
}

void Battle::BattleAct(const BattleActions action, const int choice1,
                       Creature* const target, const int choice2) {
  switch (action) {
    case BattleActions::Regenerate:
      player_->params.mana =
          min(player_->params.mana + 15, player_->params.mana_max);
      observer_->CallAct(RenderActions::kRegen, -1);
      break;
    case BattleActions::SupportSpell:
      player_->params.mana -= 20;
      observer_->CallAct(RenderActions::kSupportSpell, -1, choice1);
      player_->Offence(choice1);
      break;
    case BattleActions::Spell:
      player_->params.mana -= 20;
      PrepareCast(choice1);
      observer_->CallAct(RenderActions::kSpell, -1, choice1);
      player_->Magic(target);
      break;
    case BattleActions::PowerfulSpell:
      player_->params.mana -= 40;
      PrepareCast(choice2);
      switch (choice1) {
        case 1:
          player_->params.damage_mult *= 0;
          player_->params.status_mult *= 3;
          break;
        case 2:
          player_->params.damage_mult *= 1.5;
          player_->params.status_mult *= 1.5;
          break;
        case 3:
          player_->params.damage_mult *= 3;
          player_->params.status_mult *= 0;
          break;
        case 4:
          player_->params.damage_mult *= -1;
          player_->params.status_mult *= 4.5;
          break;
      }
      observer_->CallAct(RenderActions::kPowerfulSpell, -1, choice2);
      player_->Magic(target);
  }
  if (rand() % 101 >= player_->params.second_atk_chance) {
    for (Creature* enemy : enemies) {
      if (enemy->alive) {
        enemy->Act(player_);
      }
    }
    for (Creature* boss : stage_bosses) {
      if (boss->alive) {
        boss->Act(player_);
      }
    }
  }
  bool IsAnyEnemyAlive = false;
  for (Creature* enemy : enemies) {
    if (enemy->alive) {
      IsAnyEnemyAlive = true;
      break;
    }
  }
  for (Creature* enemy : stage_bosses) {
    if (enemy->alive) {
      IsAnyEnemyAlive = true;
      break;
    }
  }
  if (!IsAnyEnemyAlive) {
    if (stage_bosses.empty()) {
      observer_->CallAct(RenderActions::kBattleEnd);
    }
    enemies.clear();
    stage_bosses.clear();
  }
  player_->Status();
}