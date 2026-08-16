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
  if (Player->Params.Mana >= 20) {
    result.push_back(BattleActions::SupportSpell);
    result.push_back(BattleActions::Spell);
    if (Player->Params.Mana >= 40) {
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
      Player->Params.Damage = 20;
      Player->Params.Status = 5;
      Player->Params.Element = 1;
      break;
    case 2:
      Player->Params.Damage = 25;
      Player->Params.Status = 3.5;
      Player->Params.Element = 2;
      break;
    case 3:
      Player->Params.Damage = 15;
      Player->Params.Status = 7.5;
      Player->Params.Element = 3;
      break;
    case 4:
      Player->Params.Damage = 10;
      Player->Params.Status = 9;
      Player->Params.Element = 4;
      break;
  }
}

void Battle::BattleAct(BattleActions const action, int const choice1,
                       Creature* const target, int const choice2) {
  switch (action) {
    case BattleActions::Regenerate:
      Player->Params.Mana =
          min(Player->Params.Mana + 15, Player->Params.ManaMax);
      Observer->CallAct(RenderActions::Regen, -1);
      break;
    case BattleActions::SupportSpell:
      Player->Params.Mana -= 20;
      Observer->CallAct(RenderActions::SupportSpell, -1, choice1);
      Player->Offence(choice1);
      break;
    case BattleActions::Spell:
      Player->Params.Mana -= 20;
      PrepareCast(choice1);
      Observer->CallAct(RenderActions::Spell, -1, choice1);
      Player->Magic(target);
      break;
    case BattleActions::PowerfulSpell:
      Player->Params.Mana -= 40;
      PrepareCast(choice2);
      switch (choice1) {
        case 1:
          Player->Params.DamageMult *= 0;
          Player->Params.StatusMult *= 3;
          break;
        case 2:
          Player->Params.DamageMult *= 1.5;
          Player->Params.StatusMult *= 1.5;
          break;
        case 3:
          Player->Params.DamageMult *= 3;
          Player->Params.StatusMult *= 0;
          break;
        case 4:
          Player->Params.DamageMult *= -1;
          Player->Params.StatusMult *= 4.5;
          break;
      }
      Observer->CallAct(RenderActions::PowerfulSpell, -1, choice2);
      Player->Magic(target);
  }
  if (rand() % 101 >= Player->Params.SecondAtkChance) {
    for (Creature* enemy : Enemies) {
      if (enemy->Alive) {
        enemy->Act(Player);
      }
    }
    for (Creature* boss : StageBosses) {
      if (boss->Alive) {
        boss->Act(Player);
      }
    }
  }
  bool IsAnyEnemyAlive = false;
  for (Creature* enemy : Enemies) {
    if (enemy->Alive) {
      IsAnyEnemyAlive = true;
      break;
    }
  }
  for (Creature* enemy : StageBosses) {
    if (enemy->Alive) {
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