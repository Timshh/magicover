#include "battle.h"

Battle::Battle(Mage* const player, ResourceManager* const manager,
               CoreObserver* observer)
    : Teammates({player}),
      Enemies(),
      StageBosses(),
      Player(player),
      MaxEnemies(5),
      Manager(manager),
      Observer(observer) {}

void Battle::CreateBoss(int const stage) {
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

void Battle::CreateEnemy(std::string const id) {
  std::string index = id;
  if (id == "") {
    index = NormalEnemies[rand() % NormalEnemies.size()];
  }
  Enemies.push_back(new Enemy(Manager->GetCreature(index), &Enemies, Observer,
                              Enemies.size()));
}

void Battle::CreateElite(std::string const id) {
  std::string index = id;
  if (id == "") {
    index = EliteEnemies[rand() % EliteEnemies.size()];
  }
  Enemies.push_back(new Enemy(Manager->GetCreature(index), &Enemies, Observer,
                              Enemies.size()));
}

std::vector<BattleActions> Battle::BattleGetActions() {
  std::vector<BattleActions> result = {{BattleActions::Regenerate}};
  if (Player->params.Mana >= 20) {
    result.push_back(BattleActions::SupportSpell);
    result.push_back(BattleActions::Spell);
    if (Player->params.Mana >= 40) {
      result.push_back(BattleActions::PowerfulSpell);
    }
  }
  return result;
}

void Battle::BossCreator(std::string const id) {
  StageBosses.push_back(new Boss(Manager->GetCreature(id), &StageBosses,
                                 &Enemies, &MaxEnemies, Manager, Observer,
                                 StageBosses.size() + 10000));
  Observer->CallAct(RenderActions::Appear, StageBosses.size() + 9999);
}

void Battle::PrepareCast(int const choice) {
  switch (choice) {
    case 1:
      Player->params.Damage = 20;
      Player->params.Status = 5;
      Player->params.Element = 1;
      break;
    case 2:
      Player->params.Damage = 25;
      Player->params.Status = 3.5;
      Player->params.Element = 2;
      break;
    case 3:
      Player->params.Damage = 15;
      Player->params.Status = 7.5;
      Player->params.Element = 3;
      break;
    case 4:
      Player->params.Damage = 10;
      Player->params.Status = 9;
      Player->params.Element = 4;
      break;
  }
}

void Battle::BattleAct(BattleActions const action, int const choice1,
                       Creature* const target, int const choice2) {
  switch (action) {
    case BattleActions::Regenerate:
      Player->params.Mana =
          min(Player->params.Mana + 15, Player->params.ManaMax);
      Observer->CallAct(RenderActions::Regen, -1);
      break;
    case BattleActions::SupportSpell:
      Player->params.Mana -= 20;
      Observer->CallAct(RenderActions::SupportSpell, -1, choice1);
      Player->Offence(choice1);
      break;
    case BattleActions::Spell:
      Player->params.Mana -= 20;
      PrepareCast(choice1);
      Observer->CallAct(RenderActions::Spell, -1, choice1);
      Player->Magic(target);
      break;
    case BattleActions::PowerfulSpell:
      Player->params.Mana -= 40;
      PrepareCast(choice2);
      switch (choice1) {
        case 1:
          Player->params.DamageMult *= 0;
          Player->params.StatusMult *= 3;
          break;
        case 2:
          Player->params.DamageMult *= 1.5;
          Player->params.StatusMult *= 1.5;
          break;
        case 3:
          Player->params.DamageMult *= 3;
          Player->params.StatusMult *= 0;
          break;
        case 4:
          Player->params.DamageMult *= -1;
          Player->params.StatusMult *= 4.5;
          break;
      }
      Observer->CallAct(RenderActions::PowerfulSpell, -1, choice2);
      Player->Magic(target);
  }
  if (rand() % 101 >= Player->params.SecondAtkChance) {
    for (Creature* enemy : Enemies) {
      if (enemy->alive) {
        enemy->Act(Player);
      }
    }
    for (Creature* boss : StageBosses) {
      if (boss->alive) {
        boss->Act(Player);
      }
    }
  }
  bool IsAnyEnemyAlive = false;
  for (Creature* enemy : Enemies) {
    if (enemy->alive) {
      IsAnyEnemyAlive = true;
      break;
    }
  }
  for (Creature* enemy : StageBosses) {
    if (enemy->alive) {
      IsAnyEnemyAlive = true;
      break;
    }
  }
  if (!IsAnyEnemyAlive) {
    if (StageBosses.empty()) {
      Observer->CallAct(RenderActions::BattleEnd);
    }
    Enemies.clear();
    StageBosses.clear();
  }
  Player->Status();
}