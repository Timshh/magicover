#include "gamemode.h"

Gamemode::Gamemode() {}

void Gamemode::Gameloop() {
  Player = Mage(ResManager.GetCreature("Last Mage"), &Teammates, &Render);
  Teammates.push_back(&Player);
  srand(time(NULL));
  Render.PrintMessage(8, "You are the Last Mage. \nYour goal is simple - revenge."
               "To revenge for all the order slayed - to destroy their mage "
               "slayers.\n");
  Render.PrintMessage(4, "Once and for all.\n\n");
  CurrStage = MaxStage = 0;
  State = GMStates::Battle;
  int Choice;
  CreateBoss();
  while (Player.Params.HP > 0) {
    switch (State) {
      case GMStates::Map:
        DrawMap();
        break;
      case GMStates::Battle:
        do {
          int counter = 1;
          Render.PrintMessage(4, "\nEnemies\n");
          for (Creature* boss : StageBosses) {
            if (boss) {
              Render.PrintMessage(7, counter, ". ");
              counter++;
              dynamic_cast<Boss*>(boss)->Status();
            }
          }
          for (Creature* enemy : Enemies) {
            if (enemy) {
              Render.PrintMessage(7, counter, ". ");
              counter++;
              dynamic_cast<Enemy*>(enemy)->Status();
            }
          }
          Player.Status();
          std::cin >> Choice;
          switch (Choice) {
            case 1:
              Player.Params.Mana =
                  min(Player.Params.Mana + 15, Player.Params.ManaMax);
              Render.CleanRender();
              Render.PrintMessage(15, "Last Mage started regenerating\n");
              break;
            case 2:
              if (Player.Params.Mana >= 20) {
                Player.Params.Mana -= 20;
                Player.Offence();
              }
              break;
            case 3:
              if (Player.Params.Mana >= 20) {
                Player.Params.Mana -= 20;
                EnemyChooser();
                Player.Magic(Target);
              }
              break;
            case 4:
              if (Player.Params.Mana >= 40) {
                EnemyChooser();
                Player.Params.Mana -= 40;
                Render.PrintMessage(15, "Choose catalyst\n");
                Render.PrintMessage(
                   15, "1. Flame. Ignite element. Doesn't damage but increase "
                       "status much\n");
                Render.PrintMessage(
                   15, "2. Frost. Break element. Increase damage and status\n");
                Render.PrintMessage(
                   15, "3. Dark. Nullify element. Doesn't create status but "
                       "make damage bigger\n");
                Render.PrintMessage(
                   15, "4. Psycho. Overload element. Deal low heal to enemy "
                       "but add large status\n");
                std::cin >> Choice;
                switch (Choice) {
                  case 1:
                    Player.Params.DamageMult *= 0;
                    Player.Params.StatusMult *= 3;
                    break;
                  case 2:
                    Player.Params.DamageMult *= 1.5;
                    Player.Params.StatusMult *= 1.5;
                    break;
                  case 3:
                    Player.Params.DamageMult *= 3;
                    Player.Params.StatusMult *= 0;
                    break;
                  case 4:
                    Player.Params.DamageMult *= -1;
                    Player.Params.StatusMult *= 4.5;
                    break;
                  default:
                    Render.CleanRender();
                    Render.PrintMessage(4, "That didn't work\n");
                    break;
                    break;
                }
                Player.Magic(Target);
              }
              break;
            default:
              Render.CleanRender();
              Render.PrintMessage(4, "That didn't work\n");
              break;
          }
          if (rand() % 101 >= Player.Params.SecondAtkChance) {
            for (Creature* enemy : Enemies) {
              if (enemy) {
                enemy->Act(&Player);
              }
            }
            for (Creature* enemy : Enemies) {
              if (!enemy->Alive) {
                delete enemy;
              }
              
            } 
            erase_if(Enemies, [](const Creature* b) { return !b->Alive; });
            for (Creature* boss : StageBosses) {
              if (boss) {
                boss->Act(&Player);
              }
            }
            for (Creature* enemy : StageBosses) {
              if (!enemy->Alive) {
                delete enemy;
                bool IsAnyBossAlive = false;
                for (Creature* enemy : StageBosses) {
                  if (enemy->Alive) {
                    IsAnyBossAlive = true;
                    break;
                  }
                }
                if (!IsAnyBossAlive) {
                  ChangeStage();
                }
              }
            }
            erase_if(StageBosses, [](const Creature* b) { return !b->Alive; });

            if (Player.Params.HP <= 0) {
              if (Player.Params.SecondChance > 0) {
                Player.Params.SecondChance--;
                Player.Params.HP = 1;
                Render.PrintMessage(4, "\nMage refused to fall.\n");
              } else {
                Render.PrintMessage(4, "\nThe Last Mage fell.\n\n");
                exit(0);
              }
            }
          }
        } while (not StageBosses.empty() or not Enemies.empty());
        State = GMStates::Map;
        break;
      case GMStates::Inventory:
        ShowRings();
        break;
    }
  }
  Render.PrintMessage(4, "\nThe Last Mage fell.\n\n");
  return;
}

int Gamemode::TakeInt(int min, int max) {
  Render.PrintMessage(15, "Choose\n");
  int Chosen;
  do {
    while (!(std::cin >> Chosen)) {
      Render.PrintMessage(4, "Invalid choice\n");
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < min) or (Chosen > max)) {
      Render.PrintMessage(4, "Invalid choice!\n");
      std::cin.clear();
      std::cin.ignore();
    } else {
      return Chosen;
    }
  } while (true);
}

void Gamemode::CreateBoss() {
  switch (CurrStage) {
    case 0:
      StageBosses.push_back(new Boss(ResManager.GetCreature("Shield guardian"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      StageBosses.push_back(new Boss(ResManager.GetCreature("Axe guardian"),
                                     &StageBosses, &Enemies, &MaxEnemies,
                                     &ResManager,
                                     &Render));
      break;
    case 1:
      StageBosses.push_back(new Boss(ResManager.GetCreature("InfArmY"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      break;
    case 2:
      StageBosses.push_back(new Boss(ResManager.GetCreature("GO-13M"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      break;
    case 3:
      StageBosses.push_back(new Boss(ResManager.GetCreature("Wings"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      StageBosses.push_back(new Boss(ResManager.GetCreature("Tyrant"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      StageBosses.push_back(new Boss(ResManager.GetCreature("Halo"),
                                     &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager,
                                     &Render));
      break;
  }
}

void Gamemode::EnemyChooser() {
  Render.PrintMessage(15, "Choose enemy\n");
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      Render.PrintMessage(4, "Invalid target\n");
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < 1) or Chosen > (Enemies.size() + StageBosses.size())) {
      Render.PrintMessage(4, "Invalid target!\n");
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (Chosen <= StageBosses.size()) {
        Target = StageBosses[Chosen - 1];
      } else {
        Target = Enemies[Chosen - StageBosses.size() - 1];
      }
      flag = false;
    }
  } while (flag);
}

void Gamemode::ChangeStage() {
  switch (CurrStage) {
    case 0:
      Render.PrintMessage(15, "Axe guardian ring shines bright\n");
      Render.PrintMessage(2, "Ring of memories obtained\n\n");
      Player.Inventory.push_back(Ring(ResManager.GetRing("Ring of memories"), &Player));
      Render.PrintMessage(7, "Spacious outer palaces look regular");

      CoordX = 0, CoordY = 3;
      NormalEnemies = {"Hunter", "Warrior student", "Knight",
                       "Demon", "Pseudo-Witch", "Pseudo-Mage"};
      EliteEnemies = {"Archer", "Draconic hunter"};
      Map = {{"  ", "  ", "  ", "  ", "  "},   {"  ", "P-", "M-", "R ", "  "},
              {" /", "  ", " \\", " \\", "  "}, {"S-", "E-", "R-", "M-", "B "},
              {" \\", " /", " /", "  ", "  "},  {"  ", "R-", "P ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  "}};
      break;
    case 1:
      Render.PrintMessage(15, "Ring shines in the dust\n");
      Render.PrintMessage(2, "Ring of arms obtained\n\n");
      Player.Inventory.push_back(Ring(ResManager.GetRing("Ring of arms"), &Player));
      Render.PrintMessage(7, "Grandiose inner palaces shine before Last Mage");

      CoordX = 0, CoordY = 7;
      NormalEnemies = {"Demon", "Pseudo-Witch", "Pseudo-Mage",
                       "Automaton-Cleaner", "Automaton-Dog"};
      EliteEnemies = {"Automaton-Hunter", "Armored knight"};
      GetableRings.push_back("Thorn ring");
      GetableRings.push_back("Light ring");
      GetableRings.push_back("Light ring");
      GetableRings.push_back("Glass ring");
      Map = {{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
              {"  ", "  ", "  ", "P-", "R-", "R-", "R", "  ", "  ", "  "},
              {"  ", "  ", " /", "  ", " \\", " \\", " \\", "  ", "  ", "  "},
              {"  ", "  ", "R-", "R-", "E-", "R-", "M-", "R ", "  ", "  "},
              {"  ", " /", "  ", "  ", "  ", " /", "  ", " \\", "  ", "  "},
              {"  ", "P-", "M ", "  ", "  ", "R-", "E ", "  ", "R ", "  "},
              {" /", "  ", " \\", "  ", " /", "  ", " \\", "  ", " \\", "  "},
              {"S-", "E-", "R-", "P-", "P ", "  ", "E-", "R-", "R-", "B "},
              {" \\", " /", " /", "  ", " \\", " /", " /", "  ", " /", "  "},
              {"  ", "R-", "P ", "  ", "  ", "M-", "R ", "  ", "R  ", "  "},
              {"  ", " \\", "  ", "  ", "  ", "  ", "  ", " /", "  ", "  "},
              {"  ", "  ", "M ", "  ", "E-", "P-", "M-", "R ", "  ", "  "},
              {"  ", "  ", " \\", " /", "  ", " \\", " /", "  ", "  ", "  "},
              {"  ", "  ", "  ", "E-", "R-", "E-", "R ", "  ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}};
      break;
    case 2:
      Render.PrintMessage(12, "- Overheat! Overheat! Overheat...\n");
      Render.PrintMessage(
         7, "As machine turned off, its chest opened. Inside was a ring\n");
      Render.PrintMessage(2, "Clockwork ring obtained\n\n");
      Player.Inventory.push_back(Ring(ResManager.GetRing("Clockwork ring"), &Player));
      Render.PrintMessage(7, "Slayers section feels majestically.Soon it will burn");

      CoordX = 0, CoordY = 5;
      NormalEnemies = {"Pseudo-Witch",  "Pseudo-Mage",     "Automaton-Cleaner",
                       "Automaton-Dog", "Witch candidate", "Automaton-Dragon"};
      EliteEnemies = {"Slayer candidate", "Slayer"};
      GetableRings.push_back("Unstable ring");
      GetableRings.push_back("Dice ring");
      Map = {{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
              {"  ", "  ", "P-", "E-", "M-", "R ", "  ", "  "},
              {"  ", " /", "  ", "  ", " \\", " \\", "  ", "  "},
              {"  ", "P-", "E-", "R ", "  ", "P-", "E ", "  "},
              {" /", "  ", "  ", " \\", " /", "  ", " \\", "  "},
              {"S-", "E-", "R-", "M-", "P ", "  ", "P-", "B "},
              {" \\", "  ", " /", " \\", " \\", " /", " /", "  "},
              {"  ", "R-", "P ", "  ", "P ", "M ", "R ", "  "},
              {"  ", "  ", "  ", "  ", " \\", " /", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  ", "R ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "}};
      break;
    case 3:
      Render.PrintMessage(
         10, "\nYou finished the mission - you destroyed the order's core\n"
             "Congratulations, Last Mage\n\n\n");
      exit(0);
  }
  MaxStage += 1;
  CurrStage += 1;
}

bool Gamemode::NewRingChooser() {
  if (GetableRings.empty()) {
    return false;
  } else {
    int ID = rand() % GetableRings.size();
    NewRing = new Ring(ResManager.GetRing(GetableRings[ID]), &Player);
    erase(GetableRings, GetableRings[ID]);
    return true;
  }
}

void Gamemode::LocationAct() {
  int LocID = 0;
  std::string Location = Map[CoordY][CoordX].substr(0, 1);
  if (Location == "S") {
    LocID = 1;
  }
  if (Location == "E") {
    LocID = 2;
  }
  if (Location == "P") {
    LocID = 3;
  }
  if (Location == "B") {
    LocID = 4;
  }
  if (Location == "M") {
    LocID = 5;
  }
  if (Location == "R") {
    LocID = 6;
  }
  switch (LocID) {
    case 1:
      break;
    case 2:
      Render.PrintMessage(4, "Enemy appears\n");
      Enemies.push_back(new Enemy(
          ResManager.GetCreature(NormalEnemies[rand() % NormalEnemies.size()]),
                    &Enemies, &Render));
      State = GMStates::Battle;
      break;
    case 3:
      Render.PrintMessage(4, "Powerful enemy appears\n");
      Enemies.push_back(new Enemy(ResManager.GetCreature(EliteEnemies[rand() % EliteEnemies.size()]),
                    &Enemies, &Render));
      State = GMStates::Battle;
      break;
    case 4:
      CreateBoss();
      State = GMStates::Battle;
      break;
    case 5:
      Render.PrintMessage(15, "Last mage regenerate Health and Mana\n");
      Player.Params.HP = Player.Params.HPMax;
      Player.Params.Mana = Player.Params.ManaMax;
      break;
    case 6:
      int RoomType = rand() % 7 + 1;
      switch (RoomType) {
        case 1:
          Render.PrintMessage(4, "Slayer students attack Last Mage\n");
          for (int i = 0; i < (rand() % 2 + 4); i++) {
            Enemies.push_back(
                new Enemy(ResManager.GetCreature("Warrior student"), &Enemies, &Render));
          }
          State = GMStates::Battle;
          break;
        case 2:
          Render.PrintMessage(
             15, "Room have a trap\n1. Go away\n2. Get the ring in the trap\n");
          switch (TakeInt(1, 2)) {
            case 1:
              Render.PrintMessage(15, "That was a good choice\n");
              break;
            case 2:
              int TrapDmg = rand() % 10 + 5;
              Player.Params.HP -= TrapDmg;
              if (NewRingChooser()) {
                Render.PrintMessage(15, "Last Mage took a ring in cost of ");
                Render.PrintMessage(15, TrapDmg, "\n");
                Render.PrintMessage(2, NewRing->Stats.Name, " obtained", "\n");
                Player.Inventory.push_back(*NewRing);
              } else {
                Render.PrintMessage(15, "Ring were a mirage, part of trap. Last Mage were "
                             "damaged by ");
                Render.PrintMessage(15, TrapDmg);
              }
          }
          break;
        case 3:
          Render.PrintMessage(4, "Ambush!\n");
          Enemies.push_back(new Enemy(ResManager.GetCreature(EliteEnemies[0]),
                                      &Enemies, &Render));
          Enemies.push_back(new Enemy(ResManager.GetCreature(NormalEnemies[0]),
                                      &Enemies, &Render));
          State = GMStates::Battle;
          break;
        case 4:
          if (NewRingChooser()) {
            Render.PrintMessage(15, "Room contained a ring\n");
            Render.PrintMessage(15, NewRing->Stats.Name, " obtained", "\n");
            Player.Inventory.push_back(*NewRing);
          } else {
            Render.PrintMessage(15, "Room contained a ring. It turned to dust after first "
                         "touch\n");
          }
          break;
        case 5:
          Render.PrintMessage(15, "There is a demon sitting in a room. A red ring shine on his "
                 "finger. Ring Last Mage knew long ago\n");
          Render.PrintMessage(15, "- Hello there. Looks like i have a Mage here. Maybe i can "
                 "call guard... But i won't. Interested in deal? I can take "
                 "part of your health and create ring of your lifepower\n");
          Render.PrintMessage(7, "1. Accept a deal\n2. Reject the deal\n");
          switch (TakeInt(1, 2)) {
            case 1:
              Render.PrintMessage(4, "- It's a pleasure working with Mage\n");
              Render.PrintMessage(7, "As Demon cast his spell, Last mage feel that he lost "
                     "some of his health. Soon after demon give him a ring\n");
              Render.PrintMessage(4, "- Here you go. Good luck, Last Mage\n");
              Render.PrintMessage(2, "Revengeance ring obtained ", "\n");
              Player.Inventory.push_back(*NewRing);
              break;
            case 2:
              Render.PrintMessage(4, "- Well, bye then\n");
              break;
          }
          break;
        case 6:
          Render.PrintMessage(
             15, "There's cell with Mage skeleton. Last Mage can to give rest "
                 "to this Mage in cost of all Mana\n1. Do\n2. Go away");
          switch (TakeInt(1, 2)) {
            case 1:
              Render.PrintMessage(
                  15,
                  "Last Mage use all of his Mana to release Mage soul. He "
                  "feel that his Mana limit changed");
              Player.Params.Mana = 0;
              Player.Params.ManaMax += 10;
              break;
            case 2:
              Render.PrintMessage(15, "Last Mage go away");
              break;
          }
          break;
        case 7:
          Render.PrintMessage(15, "Room was empty\n");
          break;
      }
      break;
  }
}

void Gamemode::DrawMap() {
  for (int y = 0; y < Map.size(); y++) {
    for (int x = 0; x < Map[0].size(); x++) {
      if (CoordX == x and CoordY == y) {
        Render.PrintMessage(15, "*", Map[y][x].substr(1));
      } else {
        Render.PrintMessage(15, Map[y][x]);
      }
    }
    Render.PrintMessage(15, "\n");
  }
  int Deed = 2, Choice;
  Render.PrintMessage(15, "S - Start E - Enemy P - Powerful enemy B - Boss M - Mana room "
               "R - Room\n");
  Render.PrintMessage(11, "\nLast Mage\n");
  Render.PrintMessage(15, "1. Rings\n");
  if (Map[CoordY][CoordX].substr(1) == "-") {
    Render.PrintMessage(15, Deed, ". Forward\n");
    Deed++;
  }
  if (Map[CoordY - 1][CoordX].substr(1) == "/") {
    Render.PrintMessage(15, Deed, ". Left\n");
    Deed++;
  }
  if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
    Render.PrintMessage(15, Deed, ". Right\n");
    Deed++;
  }
  std::cin >> Choice;
  if (Choice < Deed and Choice > 0) {
    Deed = 0;
    switch (Choice) {
      case 1:
        GMStates::Inventory;
        Render.CleanRender();
        break;
      case 2:
        if (Map[CoordY][CoordX].substr(1) == "-") {
          CoordX++;
          Render.CleanRender();
          break;
        }
        if (Map[CoordY - 1][CoordX].substr(1) == "/") {
          CoordY -= 2;
          CoordX++;
          Render.CleanRender();
          break;
        }
        if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
          CoordY += 2;
          CoordX++;
          Render.CleanRender();
          break;
        }
        break;
      case 3:
        if (Map[CoordY][CoordX].substr(1) == "-") {
          Deed++;
        }
        if (Map[CoordY - 1][CoordX].substr(1) == "/") {
          Deed++;
          if (Deed == 2) {
            CoordY -= 2;
            CoordX++;
            Render.CleanRender();
            break;
          }
        }
        if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
          CoordY += 2;
          CoordX++;
          Render.CleanRender();
          break;
        }
        break;
      case 4:
        CoordY += 2;
        CoordX++;
        Render.CleanRender();
        break;
    }
    if (State != GMStates::Inventory) {
      LocationAct();
    }
  } else {
    Render.CleanRender();
    Render.PrintMessage(4, "That didn't work\n");
  }
}

void Gamemode::ShowRings() {
  Render.PrintMessage(15, "0. Back\n");
  for (int i = 0; i < Player.Inventory.size(); i++) {
    Render.PrintMessage(15, i + 1, ". ", Player.Inventory[i].Stats.Name);
    if (Player.Inventory[i].Stats.Equipped) {
      Render.PrintMessage(15, " - equipped");
    }
    Render.PrintMessage(15, "\n");
  }
  InventoryChooser();
  if (ChosenRing == 0) {
    return;
  }
  Render.PrintMessage(15, "1. Description\n");
  if (ChosenRing->Stats.Equipped) {
    Render.PrintMessage(15, "2. Unequip");
  } else {
    Render.PrintMessage(15, "2. Equip");
  }
  Render.PrintMessage(15, "\n3. Back\n");
  int Choose;
  std::cin >> Choose;
  switch (Choose) {
    case 1:
      Render.CleanRender();
      Render.PrintMessage(15, ChosenRing->Stats.Name, "\n");
      Render.PrintMessage(15, ChosenRing->Stats.Description, "\n");
      break;
    case 2:
      if (ChosenRing->Stats.Equipped) {
        ChosenRing->Stats.Equipped = false;
        ChosenRing->AddRingEffect(true);
        erase_if(Player.Arm, [](const Ring& r) { return !r.Stats.Equipped; });
        Render.CleanRender();
        Render.PrintMessage(15, "Uneqipped\n");
      } else {
        Equipper();
      }
      break;
    default:
      Render.CleanRender();
      break;
  }
}

void Gamemode::InventoryChooser() {
  Render.PrintMessage(15, "Choose\n");
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      Render.PrintMessage(15, "Invalid ring\n");
    }
    if (Chosen == 0) {
      ChosenRing = 0;
      flag = false;
      State = GMStates::Map;
      Render.CleanRender();
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Player.Inventory.size())) {
        Render.PrintMessage(15, "Invalid ring!\n");
      } else {
        ChosenRing = &Player.Inventory[Chosen - 1];
        flag = false;
      }
    }
  } while (flag);
}

void Gamemode::Equipper() {
  Render.PrintMessage(15, "0. Back\n");
  for (int i = 0; i < Player.Params.RingsMax; i++) {
    if (i < Player.Arm.size()) {
      Render.PrintMessage(15, i + 1, ". ", Player.Arm[i].Stats.Name, "\n");
    } else {
      Render.PrintMessage(15, i + 1, ". Empty finger\n");
      break;
    }
  }
  int Chosen, CurrSlot;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      Render.PrintMessage(15, "Invalid slot\n");
      Render.CleanRender();
    }
    if (Chosen == 0) {
      flag = false;
      Render.CleanRender();
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Player.Params.RingsMax)) {
        Render.PrintMessage(15, "Invalid slot!\n");
      } else {
        if (Chosen == Player.Arm.size() + 1) {
          Player.Arm.push_back(*ChosenRing);
          ChosenRing->Stats.Equipped = true;
          ChosenRing->AddRingEffect(true);
          Render.CleanRender();
          Render.PrintMessage(15, "Equipped\n");
          return;
        } else {
          if (Player.Arm[Chosen - 1].Stats.Uneqippable) {
            Player.Arm[Chosen - 1].Stats.Equipped = false;
            Player.Arm[Chosen - 1].AddRingEffect(false);
            erase_if(Player.Arm,
                     [](const Ring& r) { return !r.Stats.Equipped; });
            Player.Arm.push_back(*ChosenRing);
            ChosenRing->Stats.Equipped = true;
            ChosenRing->AddRingEffect(true);
            Render.CleanRender();
            Render.PrintMessage(15, "Equipped\n");
            return;
          } else {
            Render.PrintMessage(15, "This ring is not removable");
          }
        }
        flag = false;
      }
    }
  } while (flag);
}