#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <windows.h>
#include "ring.h"
#include "loader.h"
#include "enemy.h"
#include "boss.h"
#include "creature.h"

// Data for game mode
int MaxStage, CurrStage, MaxEnemies = 2, CoordX = 0, CoordY = 3, NormalRand,
                         NormalAdd, EliteRand, EliteAdd, State;
bool OSStudents = true, OSFreeRing = true, OSEmpty = true, ORDemon = true,
     ORDevil = true;
std::vector<int> GetableRings = {1, 2, 3, 4};
std::vector<std::vector<std::string>> Map;

Loader loader("external/data.json");
std::vector<Ring> Inventory;
std::vector<Ring> Arm;
Ring* ChosenRing;
std::vector<Creature*> Teammates;
std::vector<Creature*> Enemies;
std::vector<Creature*> StageBosses;
Creature Player(&loader, 2000, &Teammates);
Ring NewRing(1, &Player);
Creature* Target = 0;

void SetColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

float Clamp(float num, float min, float max) {
  if (num > max) {
    return max;
  }
  if (num < min) {
    return min;
  }
  return num;
}

int TakeInt(int Min, int Max) {
  std::cout << "Choose\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid choice\n";
    }
    if ((Chosen < Min) or (Chosen > Max)) {
      std::cout << "Invalid choice!\n";
    } else {
      return Chosen;
      flag = false;
    }
  } while (flag);
}



void Create_enemies() {
  switch (CurrStage) {
    case 0:
      StageBosses.push_back(new Boss(&loader, 1000, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      StageBosses.push_back(new Boss(&loader, 1001, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      break;
    case 1:
      StageBosses.push_back(new Boss(&loader, 1002, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      break;
    case 2:
      StageBosses.push_back(new Boss(&loader, 1003, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      break;
    case 3:
      StageBosses.push_back(new Boss(&loader, 1004, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      StageBosses.push_back(new Boss(&loader, 1005, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      StageBosses.push_back(new Boss(&loader, 1006, &StageBosses, &MaxEnemies,
                                 &Enemies, &MaxStage, &CurrStage, &CoordX,
                                 &CoordY, &NormalAdd, &NormalRand, &EliteAdd,
                                 &EliteRand, &GetableRings, &Inventory, &Map));
      break;
  }
}

void Offence() {
  int ChoiceElem;
  std::cout << "Choose spell:\n";
  std::cout << "1. Steel blood. Decrease incoming damage by half\n";
  std::cout << "2. Blue heart. Heal ";
  SetColor(4);
  std::cout << "50\n";
  SetColor(15);
  std::cout << "3. Radiance. Heal ";
  SetColor(4);
  std::cout << "80";
  SetColor(15);
  std::cout << " but incoming damage rise by half\n";
  std::cin >> ChoiceElem;
  system("cls");
  switch (ChoiceElem) {
    case 1:
      Player.Params.Defence = 0.5;
      system("cls");
      std::cout << "Last mage blood became gray. His protction rise\n";
      break;
    case 2:
      Player.Params.HP =
          Clamp(Player.Params.HP + 50, 0, Player.Params.HPMax);
      system("cls");
      std::cout
          << "Last Mage heart beat strong and slow, regenerating his health\n";
      break;
    case 3:
      Player.Params.HP = Clamp(Player.Params.HP + 80, 0, Player.Params.HPMax);
      Player.Params.Defence = 1.5;
      system("cls");
      std::cout
          << "Last Mage heart glow inside his chest, refilling his health. He "
              "is vulnerable now\n";
      break;
    default:
      system("cls");
      std::cout << "That didn't work\n";
      break;
      break;
  }
}

void Magic() {
  int ChoiceElem;
  std::cout << "Choose element:\n";
  std::cout << "1. Flame. Burn enemy slowly\n";
  std::cout << "2. Frost. Make enemy attacks weaker\n";
  std::cout << "3. Dark. With darken mind enemy may miss\n";
  std::cout << "4. Psycho. Enemy may lose control and attack self\n";
  std::cin >> ChoiceElem;
  switch (ChoiceElem) {
    case 1:
      Player.Params.Damage = 20;
      Player.Params.Status = 1;
      Player.Params.Element = 1;
      break;
    case 2:
      Player.Params.Damage = 25;
      Player.Params.Status = 0.75;
      Player.Params.Element = 2;
      break;
    case 3:
      Player.Params.Damage = 15;
      Player.Params.Status = 1.25;
      Player.Params.Element = 3;
      break;
    case 4:
      Player.Params.Damage = 10;
      Player.Params.Status = 1.5;
      Player.Params.Element = 4;
      break;
    default:
      system("cls");
      std::cout << "That didn't work\n";
      break;
      break;
  }
  system("cls");
  Target->RecieveDmg(Player.Params.Damage * Player.Params.DefaultDamageMult,
                     Player.Params.Element,
                     Player.Params.Status * Player.Params.DefaultStatusMult);
}

void EnemyChooser() {
  std::cout << "Choose enemy\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      std::cout << "Invalid target\n";
    }
    if ((Chosen < 1) or Chosen > (Enemies.size() + StageBosses.size())){
      std::cout << "Invalid target!\n";
    } else{
      if (Chosen <= StageBosses.size()) {
        Target = StageBosses[Chosen - 1];
      } else {
        Target = Enemies[Chosen - StageBosses.size() - 1];
      }
      flag = false;
    }
  } while (flag);
}

bool NewRingChooser() {
  if (GetableRings.empty()) {
    return false;
  } else {
    int ID = rand() % GetableRings.size() + 1;
    NewRing = Ring(GetableRings[ID], &Player);
    erase(GetableRings, ID);
    return true;
  }
}

void LocationAct() {
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
      Enemies.push_back(
          new Enemy(&loader, rand() % NormalRand + NormalAdd, &Enemies));
      State = 2;
      break;
    case 3:
      std::cout << "Powerful enemy appears\n";
      Enemies.push_back(
          new Enemy(&loader, rand() % EliteRand + EliteAdd, &Enemies));
      State = 2;
      break;
    case 4:
      Create_enemies();
      State = 2;
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
          for (int i = 0; i < (rand()%2 + 4); i++) {
            Enemies.push_back(
                new Enemy(&loader, 3, &Enemies));
          }
          State = 2;
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
              if (NewRingChooser()){
                std::cout << "Last Mage took a ring in cost of ";
                SetColor(15);
                std::cout << TrapDmg << std::endl;
                SetColor(2);
                std::cout << NewRing.Name << " obtained" << std::endl;
                Inventory.push_back(NewRing);
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
          Enemies.push_back(new Enemy(&loader, EliteAdd, &Enemies));
          Enemies.push_back(new Enemy(&loader, NormalAdd, &Enemies));
          State = 2;
          break;
        case 4:
          if (NewRingChooser()) {
            std::cout << "Room contained a ring\n";
            SetColor(2);
            std::cout << NewRing.Name << " obtained" << std::endl;
            SetColor(7);
            Inventory.push_back(NewRing);
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
          switch (TakeInt(1,3)) {
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
              Inventory.push_back(NewRing);
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
          switch (TakeInt(1,2)) { 
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

void DrawMap() { 
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
  std::cout << "1. Inventory\n";
  if (Map[CoordY][CoordX].substr(1) == "-") {
    std::cout << Deed << ". Forward\n";
    Deed++;
  }
  if (Map[CoordY - 1][CoordX].substr(1) == "/") {
    std::cout << Deed << ". Left\n";
    Deed++;
  }
  if (Map[CoordY + 1][CoordX].substr(1,2) == "\\") {
    std::cout << Deed << ". Right\n";
    Deed++;
  }
  std::cin >> Choice;
  if (Choice < Deed and Choice > 0) {
    Deed = 0;
    switch (Choice) {
      case 1:
        State = 3;
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
    if (State != 3) {
      LocationAct();
    }
  } else {
    system("cls");
    std::cout << "That didn't work\n";
  }
}

void InventoryChooser();
void Equipper();

void ShowRings() {
  std::cout << "0. Back\n";
  for (int i = 0; i < Inventory.size(); i++) {
    std::cout << i + 1 << ". " << Inventory[i].Name;
    if (Inventory[i].Equipped) {
      std::cout << " - equipped";
    }
    std::cout << std::endl;
  }
  InventoryChooser();
  if (ChosenRing == 0) {
    return;
  }
  std::cout << "1. Description\n";
  if (ChosenRing->Equipped) {
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
      std::cout << ChosenRing->Name << std::endl;
      std::cout << ChosenRing->Description << std::endl;
      break;
    case 2:
      if (ChosenRing->Equipped) {
        ChosenRing->Equipped = false;
        ChosenRing->AddRingEffect(true);
        erase_if(Arm, [](const Ring& r) { return !r.Equipped; });
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

void InventoryChooser() {
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
      State = 1;
      system("cls");
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Inventory.size())) {
        std::cout << "Invalid ring!\n";
      } else {
        ChosenRing = &Inventory[Chosen - 1];
        flag = false;
      }
    }
  } while (flag);
}

void Equipper() {
  std::cout << "0. Back\n";
  for (int i = 0; i < Player.Params.RingsMax; i++) {
    if (i < Arm.size()) {
      std::cout << i + 1 << ". " << Arm[i].Name << std::endl;
    } else {
      std::cout << i + 1 << ". Empty\n";
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
      if ((Chosen < 1) or Chosen > (Arm.size()+1)) {
        std::cout << "Invalid slot!\n";
      } else {
        if (Chosen == Arm.size() + 1) {
          Arm.push_back(*ChosenRing);
          ChosenRing->Equipped = true;
          ChosenRing->AddRingEffect(true);
          system("cls");
          std::cout << "Equipped\n";
          return;
        } else {
          if (Arm[Chosen-1].Uneqippable) {
            Arm[Chosen - 1].Equipped = false;
            Arm[Chosen - 1].AddRingEffect(false);
            erase_if(Arm, [](const Ring& r) { return !r.Equipped; });
            Arm.push_back(*ChosenRing);
            ChosenRing->Equipped = true;
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

int main() {
  Player = Creature(&loader, 2000, &Teammates);
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
  Player.Params.HP = Player.Params.HPMax = 100;
  Player.Params.Mana = Player.Params.ManaMax = 100;
  Player.Params.Defence = 1;
  State = 2;
  int Choice;
  Create_enemies();
  while (Player.Params.HP > 0) {
    switch (State) {
      case 1:
        DrawMap();
        break;
      case 2:
        do {
          int counter = 1;
          Player.Params.Defence = Player.Params.DefaultDefence;
          //DamageMult = DefaultDamageMult;
          //StatusMult = DefaultStatusMult;
          SetColor(4);
          std::cout << "\nEnemies\n";
          SetColor(7);
          for (Creature* boss : StageBosses) {
            if (boss) {
              std::cout << counter << ". ";
              counter++;
              dynamic_cast<Boss*>(boss)->Stats();
            }
          }
          for (Creature* enemy : Enemies) {
            if (enemy) {
              std::cout << counter << ". ";
              counter++;
              dynamic_cast<Enemy*>(enemy)->Stats();
            }
          }
          SetColor(11);
          std::cout << "\nLast Mage\n";
          SetColor(15);
          std::cout << "Health: ";
          SetColor(4);
          std::cout << Player.Params.HP;
          SetColor(15);
          std::cout << " Mana: ";
          SetColor(3);
          std::cout << Player.Params.Mana << "\n";
          SetColor(15);
          std::cout << "1. Regenerate. Gain ";
          SetColor(3);
          std::cout << "15\n";
          SetColor(15);
          if (Player.Params.Mana >= 20) {
            std::cout
                << "2. Support with spell. ";
            SetColor(3);
            std::cout << "20\n";
            SetColor(15);
            std::cout << "3. Attack with one element. ";
            SetColor(3);
            std::cout << "20\n";
            SetColor(15);
            if (Player.Params.Mana >= 40) {
              std::cout << "4. Attack with two elements. ";
              SetColor(3);
              std::cout << "40\n";
              SetColor(15);
            }
          }
          SetColor(15);
          std::cin >> Choice;
          switch (Choice) {
            case 1:
              Player.Params.Mana =
                  Clamp(Player.Params.Mana + 15, 0,Player.Params.ManaMax);
              system("cls");
              std::cout << "Last Mage started regenerating\n";
              break;
            case 2:
              if (Player.Params.Mana >= 20) {
                Player.Params.Mana -= 20;
                Offence();
              }
              break;
            case 3:
              if (Player.Params.Mana >= 20) {
                Player.Params.Mana -= 20;
                EnemyChooser();
                Magic();
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
                    Player.Params.DefaultDamageMult *= 0;
                    Player.Params.DefaultStatusMult *= 3;
                    break;
                  case 2:
                    Player.Params.DefaultDamageMult *= 1.5;
                    Player.Params.DefaultStatusMult *= 1.5;
                    break;
                  case 3:
                    Player.Params.DefaultDamageMult *= 3;
                    Player.Params.DefaultStatusMult *= 0;
                    break;
                  case 4:
                    Player.Params.DefaultDamageMult *= -1;
                    Player.Params.DefaultStatusMult *= 4.5;
                    break;
                  default:
                    system("cls");
                    std::cout << "That didn't work\n";
                    break;
                    break;
                }
                Magic();
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
            for (Creature* boss : StageBosses) {
              if (boss) {
                boss->Act(&Player);
              }
            }
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
          Player.Params.Mana =
              Clamp(Player.Params.Mana + 15, 0, Player.Params.ManaMax);
          for (Ring& currRing : Arm) {
            currRing.RingAct();
          }
        } while (not StageBosses.empty() or not Enemies.empty());
        State = 1;
        break;
      case 3:
        ShowRings();
        break;
    }
  }
  SetColor(4);
  std::cout << "\nThe Last Mage fell.\n\n";
  SetColor(15);
  exit(0);
}