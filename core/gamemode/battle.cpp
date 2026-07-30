#include "battle.h"

Battle::Battle(ConsoleRenderer* globalRender, Renderer* render,
               std::vector<Creature*>* const teammates,
               std::vector<Creature*>* const enemies,
               std::vector<Creature*>* const stageBosses, Mage* player,
               int* const stage,
               int* const maxEnemies, ResourceManager* const manager)
    : GlobalRender(globalRender),
      Render(render),
      Teammates(teammates),
      Enemies(enemies),
      StageBosses(stageBosses),
      Player(player),  
    Stage(stage),
      MaxEnemies(maxEnemies),
      Manager(manager) {}

void Battle::EnemyChooser() {
  GlobalRender->PrintMessage(15, "Choose enemy\n");
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      GlobalRender->PrintMessage(4, "Invalid target\n");
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < 1) or Chosen > (Enemies->size() + StageBosses->size())) {
      GlobalRender->PrintMessage(4, "Invalid target!\n");
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (Chosen <= StageBosses->size()) {
        Target = StageBosses->at(Chosen - 1);
      } else {
        Target = Enemies->at(Chosen - StageBosses->size() - 1);
      }
      flag = false;
    }
  } while (flag);
}

void Battle::CreateBoss() {
  switch (*Stage) {
    case 0:
      StageBosses->push_back(new Boss(Manager->GetCreature("Shield guardian"),
                                      StageBosses, Enemies, MaxEnemies,
                                      Manager, GlobalRender, Render));
      StageBosses->push_back(new Boss(Manager->GetCreature("Axe guardian"),
                                      StageBosses, Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      break;
    case 1:
      StageBosses->push_back(new Boss(Manager->GetCreature("InfArmY"),
                                      StageBosses, Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      break;
    case 2:
      StageBosses->push_back(new Boss(Manager->GetCreature("GO-13M"),
                                      StageBosses, Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      break;
    case 3:
      StageBosses->push_back(new Boss(Manager->GetCreature("Wings"),
                                      StageBosses, Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      StageBosses->push_back(new Boss(Manager->GetCreature("Tyrant"),
                                      StageBosses, Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      StageBosses->push_back(new Boss(Manager->GetCreature("Halo"), StageBosses,
                                      Enemies, MaxEnemies, Manager,
                                      GlobalRender, Render));
      break;
  }
}

bool Battle::StartBattle() {
  int Choice;
  do {
    int counter = 1;
    GlobalRender->PrintMessage(4, "\nEnemies\n");
    for (Creature* boss : *StageBosses) {
      if (boss) {
        GlobalRender->PrintMessage(7, counter, ". ");
        counter++;
        dynamic_cast<Boss*>(boss)->Status();
      }
    }
    for (Creature* enemy : *Enemies) {
      if (enemy) {
        GlobalRender->PrintMessage(7, counter, ". ");
        counter++;
        dynamic_cast<Enemy*>(enemy)->Status();
      }
    }
    Player->Status();
    std::cin >> Choice;
    switch (Choice) {
      case 1:
        Player->Params.Mana =
            min(Player->Params.Mana + 15, Player->Params.ManaMax);
        GlobalRender->CleanRender();
        GlobalRender->PrintMessage(15, "Last Mage started regenerating\n");
        break;
      case 2:
        if (Player->Params.Mana >= 20) {
          Player->Params.Mana -= 20;
          Player->Offence();
        }
        break;
      case 3:
        if (Player->Params.Mana >= 20) {
          Player->Params.Mana -= 20;
          EnemyChooser();
          Player->Magic(Target);
        }
        break;
      case 4:
        if (Player->Params.Mana >= 40) {
          EnemyChooser();
          Player->Params.Mana -= 40;
          GlobalRender->PrintMessage(15, "Choose catalyst\n");
          GlobalRender->PrintMessage(
              15,
              "1. Flame. Ignite element. Doesn't damage but increase "
              "status much\n");
          GlobalRender->PrintMessage(
              15, "2. Frost. Break element. Increase damage and status\n");
          GlobalRender->PrintMessage(
              15,
              "3. Dark. Nullify element. Doesn't create status but "
              "make damage bigger\n");
          GlobalRender->PrintMessage(
              15,
              "4. Psycho. Overload element. Deal low heal to enemy "
              "but add large status\n");
          std::cin >> Choice;
          switch (Choice) {
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
            default:
              GlobalRender->CleanRender();
              GlobalRender->PrintMessage(4, "That didn't work\n");
              break;
              break;
          }
          Player->Magic(Target);
        }
        break;
      default:
        GlobalRender->CleanRender();
        GlobalRender->PrintMessage(4, "That didn't work\n");
        break;
    }
    if (rand() % 101 >= Player->Params.SecondAtkChance) {
      for (Creature* enemy : *Enemies) {
        if (enemy) {
          enemy->Act(Player);
        }
      }
      for (Creature* enemy : *Enemies) {
        if (!enemy->Alive) {
          delete enemy;
          erase(*Enemies, enemy);
        }
      }

      for (Creature* boss : *StageBosses) {
        if (boss) {
          boss->Act(Player);
        }
      }
      for (Creature* enemy : *StageBosses) {
        if (!enemy->Alive) {
          delete enemy;
          erase(*StageBosses, enemy);
          bool IsAnyBossAlive = false;
          for (Creature* enemy : *StageBosses) {
            if (enemy->Alive) {
              IsAnyBossAlive = true;
              break;
            }
          }
          if (!IsAnyBossAlive) {
            return true;
          }
        }
      }

      if (Player->Params.HP <= 0) {
        if (Player->Params.SecondChance > 0) {
          Player->Params.SecondChance--;
          Player->Params.HP = 1;
          GlobalRender->PrintMessage(4, "\nMage refused to fall.\n");
        } else {
          GlobalRender->PrintMessage(4, "\nThe Last Mage fell.\n\n");
          exit(0);
        }
      }
    }
  } while (not StageBosses->empty() or not Enemies->empty());
  return false;
}