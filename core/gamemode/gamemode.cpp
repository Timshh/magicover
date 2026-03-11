#include "gamemode.h"

Gamemode::Gamemode() {}

void Gamemode::Gameloop() {
  Player = Mage(ResManager.GetCreature(2000), &Teammates);
  Teammates.push_back(&Player);
  srand(time(NULL));
  SetColor(8);
  std::cout << "You are the Last Mage. \nYour goal is simple - revenge."
               "To revenge for all the order slayed - to destroy their mage "
               "slayers.\n";
  SetColor(4);
  std::cout << "Once and for all.\n\n";
  SetColor(7);
  CurrStage = MaxStage = 0;
  State = GMStates::Battle;
  int Choice;
  Create_enemies();
  while (Player.Params.HP > 0) {
    switch (State) {
      case GMStates::Map:
        DrawMap();
        break;
      case GMStates::Battle:
        do {
          int counter = 1;
          SetColor(4);
          std::cout << "\nEnemies\n";
          SetColor(7);
          for (Creature* boss : StageBosses) {
            if (boss) {
              std::cout << counter << ". ";
              counter++;
              dynamic_cast<Boss*>(boss)->Status();
            }
          }
          for (Creature* enemy : Enemies) {
            if (enemy) {
              std::cout << counter << ". ";
              counter++;
              dynamic_cast<Enemy*>(enemy)->Status();
            }
          }
          Player.Status();
          SetColor(15);
          std::cin >> Choice;
          switch (Choice) {
            case 1:
              Player.Params.Mana =
                  Clamp(Player.Params.Mana + 15, 0, Player.Params.ManaMax);
              system("cls");
              std::cout << "Last Mage started regenerating\n";
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
                std::cout << "Choose catalyst\n";
                std::cout
                    << "1. Flame. Ignite element. Doesn't damage but increase "
                       "status much\n";
                std::cout
                    << "2. Frost. Break element. Increase damage and status\n";
                std::cout
                    << "3. Dark. Nullify element. Doesn't create status but "
                       "make damage bigger\n";
                std::cout
                    << "4. Psycho. Overload element. Deal low heal to enemy "
                       "but add large status\n";
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
                    system("cls");
                    std::cout << "That didn't work\n";
                    break;
                    break;
                }
                Player.Magic(Target);
              }
              break;
            default:
              system("cls");
              std::cout << "That didn't work\n";
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
                std::cout << "\nMage refused to fall.\n";
              } else {
                SetColor(4);
                std::cout << "\nThe Last Mage fell.\n\n";
                SetColor(15);
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
  SetColor(4);
  std::cout << "\nThe Last Mage fell.\n\n";
  SetColor(15);
  return;
}

int Gamemode::TakeInt(int min, int max) {
  std::cout << "Choose\n";
  int Chosen;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid choice\n";
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < min) or (Chosen > max)) {
      std::cout << "Invalid choice!\n";
      std::cin.clear();
      std::cin.ignore();
    } else {
      return Chosen;
    }
  } while (true);
}

float Gamemode::Clamp(float num, float min, float max) {
  if (num > max) {
    return max;
  }
  if (num < min) {
    return min;
  }
  return num;
}

void Gamemode::SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void Gamemode::Create_enemies() {
  switch (CurrStage) {
    case 0:
      StageBosses.push_back(new Boss(ResManager.GetCreature(1000), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      StageBosses.push_back(new Boss(ResManager.GetCreature(1001), &StageBosses, &Enemies,
                                     &MaxEnemies, &ResManager));
      break;
    case 1:
      StageBosses.push_back(new Boss(ResManager.GetCreature(1002), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      break;
    case 2:
      StageBosses.push_back(new Boss(ResManager.GetCreature(1003), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      break;
    case 3:
      StageBosses.push_back(new Boss(ResManager.GetCreature(1004), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      StageBosses.push_back(new Boss(ResManager.GetCreature(1005), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      StageBosses.push_back(new Boss(ResManager.GetCreature(1006), &StageBosses,
                                     &Enemies, &MaxEnemies, &ResManager));
      break;
  }
}

void Gamemode::EnemyChooser() {
  std::cout << "Choose enemy\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid target\n";
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < 1) or Chosen > (Enemies.size() + StageBosses.size())) {
      std::cout << "Invalid target!\n";
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
      std::cout << "Axe guardian ring shines bright\n";
      SetColor(2);
      std::cout << "Ring of memories obtained\n\n";
      Player.Inventory.push_back(Ring(ResManager.GetRing(0), &Player));
      SetColor(7);
      std::cout << "Spacious outer palaces look regular";
      CoordX = 0, CoordY = 3;
      EliteAdd = 20;
      EliteRand = 2;
      NormalAdd = 1;
      NormalRand = 4;
      Map = {{"  ", "  ", "  ", "  ", "  "},   {"  ", "P-", "M-", "R ", "  "},
              {" /", "  ", " \\", " \\", "  "}, {"S-", "E-", "R-", "M-", "B "},
              {" \\", " /", " /", "  ", "  "},  {"  ", "R-", "P ", "  ", "  "},
              {"  ", "  ", "  ", "  ", "  "}};
      break;
    case 1:
      std::cout << "Ring shines in the dust\n";
      SetColor(2);
      std::cout << "Ring of arms obtained\n\n";
      Player.Inventory.push_back(Ring(ResManager.GetRing(888), &Player));
      SetColor(7);
      std::cout << "Grandiose inner palaces shine before Last Mage";
      CoordX = 0, CoordY = 7;
      EliteAdd = 21;
      EliteRand = 4;
      NormalAdd = 2;
      NormalRand = 5;
      GetableRings.push_back(5);
      GetableRings.push_back(6);
      GetableRings.push_back(7);
      GetableRings.push_back(8);
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
      SetColor(12);
      std::cout << "- Overheat! Overheat! Overheat...\n";
      SetColor(7);
      std::cout
          << "As machine turned off, its chest opened. Inside was a ring\n";
      SetColor(2);
      std::cout << "Clockwork ring obtained\n\n";
      Player.Inventory.push_back(Ring(ResManager.GetRing(1834), &Player));
      SetColor(7);
      std::cout << "Slayers section feels majestically.Soon it will burn";
      CoordX = 0, CoordY = 5;
      EliteAdd = 23;
      EliteRand = 3;
      NormalAdd = 5;
      NormalRand = 5;
      GetableRings.push_back(9);
      GetableRings.push_back(10);
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
      SetColor(10);
      std::cout
          << "\nYou finished the mission - you destroyed the order's core\n"
             "Congratulations, Last Mage\n\n\n";
      SetColor(7);
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
    NewRing = Ring(ResManager.GetRing(GetableRings[ID]), &Player);
    erase(GetableRings, ID);
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
      std::cout << "Enemy appears\n";
      Enemies.push_back(new Enemy(
          ResManager.GetCreature(rand() % NormalRand + NormalAdd), &Enemies));
      State = GMStates::Battle;
      break;
    case 3:
      std::cout << "Powerful enemy appears\n";
      Enemies.push_back(new Enemy(
          ResManager.GetCreature(rand() % EliteRand + EliteAdd), &Enemies));
      State = GMStates::Battle;
      break;
    case 4:
      Create_enemies();
      State = GMStates::Battle;
      break;
    case 5:
      std::cout << "Last mage regenerate Health and Mana\n";
      Player.Params.HP = Player.Params.HPMax;
      Player.Params.Mana = Player.Params.ManaMax;
      break;
    case 6:
      int RoomType = rand() % 7 + 1;
      switch (RoomType) {
        case 1:
          std::cout << "Slayer students attack Last Mage\n";
          for (int i = 0; i < (rand() % 2 + 4); i++) {
            Enemies.push_back(new Enemy(ResManager.GetCreature(3), &Enemies));
          }
          State = GMStates::Battle;
          break;
        case 2:
          std::cout
              << "Room have a trap\n1. Go away\n2. Get the ring in the trap\n";
          switch (TakeInt(1, 2)) {
            case 1:
              std::cout << "That was a good choice\n";
              break;
            case 2:
              int TrapDmg = rand() % 10 + 5;
              Player.Params.HP -= TrapDmg;
              if (NewRingChooser()) {
                std::cout << "Last Mage took a ring in cost of ";
                SetColor(15);
                std::cout << TrapDmg << std::endl;
                SetColor(2);
                std::cout << NewRing.Stats.Name << " obtained" << std::endl;
                Player.Inventory.push_back(NewRing);
                SetColor(7);
              } else {
                std::cout << "Ring were a mirage, part of trap. Last Mage were "
                             "damaged by ";
                SetColor(15);
                std::cout << TrapDmg << std::endl;
                SetColor(7);
              }
          }
          break;
        case 3:
          std::cout << "Ambush!\n";
          Enemies.push_back(
              new Enemy(ResManager.GetCreature(EliteAdd), &Enemies));
          Enemies.push_back(
              new Enemy(ResManager.GetCreature(NormalAdd), &Enemies));
          State = GMStates::Battle;
          break;
        case 4:
          if (NewRingChooser()) {
            std::cout << "Room contained a ring\n";
            SetColor(2);
            std::cout << NewRing.Stats.Name << " obtained" << std::endl;
            SetColor(7);
            Player.Inventory.push_back(NewRing);
          } else {
            std::cout << "Room contained a ring. It turned to dust after first "
                         "touch\n";
          }
          break;
        case 5:
          std::cout
              << "There is a demon sitting in a room. A red ring shine on his "
                 "finger. Ring Last Mage knew long ago\n";
          SetColor(4);
          std::cout
              << "- Hello there. Looks like i have a Mage here. Maybe i can "
                 "call guard... But i won't. Interested in deal? I can take "
                 "part of your health and create ring of your lifepower\n";
          SetColor(7);
          std::cout << "1. Accept a deal\n2. Reject the deal\n";
          switch (TakeInt(1, 3)) {
            case 1:
              SetColor(4);
              std::cout << "- It's a pleasure working with Mage\n";
              SetColor(7);
              std::cout
                  << "As Demon cast his spell, Last mage feel that he lost "
                     "some of his health. Soon after demon give him a ring\n";
              SetColor(4);
              std::cout << "- Here you go. Good luck, Last Mage\n";
              SetColor(2);
              std::cout << "Revengeance ring obtained " << std::endl;
              SetColor(7);
              Player.Inventory.push_back(NewRing);
              break;
            case 2:
              SetColor(4);
              std::cout << "- Well, bye then\n";
              SetColor(7);
              break;
          }
          break;
        case 6:
          std::cout
              << "There's cell with Mage skeleton. Last Mage can to give rest "
                 "to this Mage in cost of all Mana\n1. Do\n2. Go away";
          switch (TakeInt(1, 2)) {
            case 1:
              std::cout
                  << "Last Mage use all of his Mana to release Mage soul. He "
                     "feel that his Mana limit changed";
              Player.Params.Mana = 0;
              Player.Params.ManaMax += 10;
              break;
            case 2:
              std::cout << "Last Mage go away";
              break;
          }
          break;
        case 7:
          std::cout << "Room was empty\n";
          break;
      }
      break;
  }
}

void Gamemode::DrawMap() {
  for (int y = 0; y < Map.size(); y++) {
    for (int x = 0; x < Map[0].size(); x++) {
      if (CoordX == x and CoordY == y) {
        std::cout << "*" << Map[y][x].substr(1);
      } else {
        std::cout << Map[y][x];
      }
    }
    std::cout << std::endl;
  }
  int Deed = 2, Choice;
  std::cout << "S - Start E - Enemy P - Powerful enemy B - Boss M - Mana room "
               "R - Room\n";
  SetColor(11);
  std::cout << "\nLast Mage\n";
  SetColor(15);
  std::cout << "1. Rings\n";
  if (Map[CoordY][CoordX].substr(1) == "-") {
    std::cout << Deed << ". Forward\n";
    Deed++;
  }
  if (Map[CoordY - 1][CoordX].substr(1) == "/") {
    std::cout << Deed << ". Left\n";
    Deed++;
  }
  if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
    std::cout << Deed << ". Right\n";
    Deed++;
  }
  std::cin >> Choice;
  if (Choice < Deed and Choice > 0) {
    Deed = 0;
    switch (Choice) {
      case 1:
        GMStates::Inventory;
        system("cls");
        break;
      case 2:
        if (Map[CoordY][CoordX].substr(1) == "-") {
          CoordX++;
          system("cls");
          break;
        }
        if (Map[CoordY - 1][CoordX].substr(1) == "/") {
          CoordY -= 2;
          CoordX++;
          system("cls");
          break;
        }
        if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
          CoordY += 2;
          CoordX++;
          system("cls");
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
            system("cls");
            break;
          }
        }
        if (Map[CoordY + 1][CoordX].substr(1, 2) == "\\") {
          CoordY += 2;
          CoordX++;
          system("cls");
          break;
        }
        break;
      case 4:
        CoordY += 2;
        CoordX++;
        system("cls");
        break;
    }
    if (State != GMStates::Inventory) {
      LocationAct();
    }
  } else {
    system("cls");
    std::cout << "That didn't work\n";
  }
}

void Gamemode::ShowRings() {
  std::cout << "0. Back\n";
  for (int i = 0; i < Player.Inventory.size(); i++) {
    std::cout << i + 1 << ". " << Player.Inventory[i].Stats.Name;
    if (Player.Inventory[i].Stats.Equipped) {
      std::cout << " - equipped";
    }
    std::cout << std::endl;
  }
  InventoryChooser();
  if (ChosenRing == 0) {
    return;
  }
  std::cout << "1. Description\n";
  if (ChosenRing->Stats.Equipped) {
    std::cout << "2. Unequip";
  } else {
    std::cout << "2. Equip";
  }
  std::cout << "\n3. Back\n";
  int Choose;
  std::cin >> Choose;
  switch (Choose) {
    case 1:
      system("cls");
      std::cout << ChosenRing->Stats.Name << std::endl;
      std::cout << ChosenRing->Stats.Description << std::endl;
      break;
    case 2:
      if (ChosenRing->Stats.Equipped) {
        ChosenRing->Stats.Equipped = false;
        ChosenRing->AddRingEffect(true);
        erase_if(Player.Arm, [](const Ring& r) { return !r.Stats.Equipped; });
        system("cls");
        std::cout << "Uneqipped\n";
      } else {
        Equipper();
      }
      break;
    default:
      system("cls");
      break;
  }
}

void Gamemode::InventoryChooser() {
  std::cout << "Choose\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid ring\n";
    }
    if (Chosen == 0) {
      ChosenRing = 0;
      flag = false;
      State = GMStates::Map;
      system("cls");
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Player.Inventory.size())) {
        std::cout << "Invalid ring!\n";
      } else {
        ChosenRing = &Player.Inventory[Chosen - 1];
        flag = false;
      }
    }
  } while (flag);
}

void Gamemode::Equipper() {
  std::cout << "0. Back\n";
  for (int i = 0; i < Player.Params.RingsMax; i++) {
    if (i < Player.Arm.size()) {
      std::cout << i + 1 << ". " << Player.Arm[i].Stats.Name << std::endl;
    } else {
      std::cout << i + 1 << ". Empty finger\n";
      break;
    }
  }
  int Chosen, CurrSlot;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid slot\n";
    }
    if (Chosen == 0) {
      flag = false;
      system("cls");
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Player.Params.RingsMax)) {
        std::cout << "Invalid slot!\n";
      } else {
        if (Chosen == Player.Arm.size() + 1) {
          Player.Arm.push_back(*ChosenRing);
          ChosenRing->Stats.Equipped = true;
          ChosenRing->AddRingEffect(true);
          system("cls");
          std::cout << "Equipped\n";
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
            system("cls");
            std::cout << "Equipped\n";
            return;
          } else {
            std::cout << "This ring is not removable";
          }
        }
        flag = false;
      }
    }
  } while (flag);
}