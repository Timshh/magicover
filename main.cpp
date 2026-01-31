#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <windows.h>
#include "ring.h"
#include "enemy.h"
#include "boss.h"

using namespace std;
int MainHP, MainHPMax, MaxStage, CurrStage, Mana, ManaMax, Element,
    SecondChance = 0, SecondAtkChance = 0, RingsMax = 5, MaxEnemies = 2,
    CoordX = 0, CoordY = 3, NormalRand, NormalAdd, EliteRand,
    EliteAdd, State;
float Dmg, Status, Defence, DamageMult, StatusMult, DefaultDefence = 1,
    DefaultDamageMult = 1, DefaultStatusMult = 1;
bool OSStudents = true, OSFreeRing = true, OSEmpty = true, ORDemon = true,
     ORDevil = true;

vector<int> GetableRings = {1, 2, 3, 4};
vector<vector<string>> Map;

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
  cout << "Choose\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(cin >> Chosen)) {
      cout << "Invalid choice\n";
    }
    if ((Chosen < Min) or (Chosen > Max)) {
      cout << "Invalid choice!\n";
    } else {
      return Chosen;
      flag = false;
    }
  } while (flag);
}

Ring NewRing(1);
vector<Ring> Inventory;
vector<Ring> Arm;
Ring* ChosenRing;
vector<Enemy> Enemies;
vector<Boss> StageBosses;
Enemy* Target = 0;


void Create_enemies() {
  switch (CurrStage) {
    case 0:
      StageBosses.push_back(Boss(0));
      StageBosses.push_back(Boss(1));
      break;
    case 1:
      StageBosses.push_back(Boss(2));
      break;
    case 2:
      StageBosses.push_back(Boss(3));
      break;
    case 3:
      StageBosses.push_back(Boss(4));
      StageBosses.push_back(Boss(5));
      StageBosses.push_back(Boss(6));
      break;
  }
}

void Offence() {
  int ChoiceElem;
  cout << "Choose spell:\n";
  cout << "1. Steel blood. Decrease incoming damage by half\n";
  cout << "2. Blue heart. Heal ";
  SetColor(4);
  cout << "50\n";
  SetColor(15);
  cout << "3. Radiance. Heal ";
  SetColor(4);
  cout << "80";
  SetColor(15);
  cout << " but incoming damage rise by half\n";
  cin >> ChoiceElem;
  system("cls");
  switch (ChoiceElem) {
    case 1:
      Defence = 0.5;
      system("cls");
      cout << "Last mage blood became gray. His protction rise\n";
      break;
    case 2:
      MainHP = Clamp(MainHP + 50, 0, MainHPMax);
      system("cls");
      cout << "Last Mage heart beat strong and slow, regenerating his health\n";
      break;
    case 3:
      MainHP = Clamp(MainHP + 80, 0, MainHPMax);
      Defence = 1.5;
      system("cls");
      cout << "Last Mage heart glow inside his chest, refilling his health. He "
              "is vulnerable now\n";
      break;
    default:
      system("cls");
      cout << "That didn't work\n";
      break;
      break;
  }
}

void Magic() {
  int ChoiceElem;
  cout << "Choose element:\n";
  cout << "1. Flame. Burn enemy slowly\n";
  cout << "2. Frost. Make enemy attacks weaker\n";
  cout << "3. Dark. With darken mind enemy may miss\n";
  cout << "4. Psycho. Enemy may lose control and attack self\n";
  cin >> ChoiceElem;
  switch (ChoiceElem) {
    case 1:
      Dmg = 20;
      Status = 1;
      Element = 1;
      break;
    case 2:
      Dmg = 25;
      Status = 0.75;
      Element = 2;
      break;
    case 3:
      Dmg = 15;
      Status = 1.25;
      Element = 3;
      break;
    case 4:
      Dmg = 10;
      Status = 1.5;
      Element = 4;
      break;
    default:
      system("cls");
      cout << "That didn't work\n";
      break;
      break;
  }
  system("cls");
  Target->RecieveDmg(&Dmg, &DamageMult, &Element, &Status, &StatusMult,
                     &Enemies);
}

void EnemyChooser() {
  cout << "Choose enemy\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(cin >> Chosen)) {
      cout << "Invalid target\n";
    }
    if ((Chosen < 1) or Chosen > (Enemies.size() + StageBosses.size())){
      cout << "Invalid target!\n";
    } else{
      if (Chosen <= StageBosses.size()) {
        Target = &StageBosses[Chosen - 1];
      } else {
        Target = &Enemies[Chosen - StageBosses.size() - 1];
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
    NewRing = Ring(GetableRings[ID]);
    erase(GetableRings, ID);
    return true;
  }
}

void LocationAct() {
  int LocID = 0;
  string Location = Map[CoordY][CoordX].substr(0,1);
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
      cout << "Enemy appears\n";
      Enemies.push_back(Enemy(rand() % NormalRand + NormalAdd));
      State = 2;
      break;
    case 3:
        cout << "Powerful enemy appears\n";
        Enemies.push_back(Enemy(rand() % NormalRand + NormalAdd));
      State = 2;
      break;
    case 4:
      Create_enemies();
      State = 2;
      break;
    case 5:
      cout << "Last mage regenerate Health and Mana\n";
      MainHP = MainHPMax;
      Mana = ManaMax;
      break;
    case 6:
      int RoomType = rand() % 7 + 1;
      switch (RoomType) {
        case 1:
          cout << "Slayer students attack Last Mage\n";
          for (int i = 0; i < (rand()%2 + 4); i++) {
            Enemies.push_back(Enemy(3));
          }
          State = 2;
          break;
        case 2:
          cout << "Room have a trap\n1. Go away\n2. Get the ring in the trap\n";
          switch (TakeInt(1, 2)) { 
            case 1:
              cout << "That was a good choice\n";
              break;
            case 2:
              int TrapDmg = rand() % 10 + 5;
              MainHP -= TrapDmg;
              if (NewRingChooser()){
                cout << "Last Mage took a ring in cost of ";
                SetColor(15);
                cout << TrapDmg << endl;
                SetColor(2);
                cout << NewRing.Name << " obtained" << endl;
                Inventory.push_back(NewRing);
                SetColor(7);
              } else {
                cout << "Ring were a mirage, part of trap. Last Mage were damaged by ";
                SetColor(15);
                cout << TrapDmg << endl;
                SetColor(7);
              }    
          }
          break;
        case 3:
          cout << "Ambush!\n";
          Enemies.push_back(Enemy(EliteAdd));
          Enemies.push_back(Enemy(NormalAdd));
          State = 2;
          break;
        case 4:
          if (NewRingChooser()) {
            cout << "Room contained a ring\n";
            SetColor(2);
            cout << NewRing.Name << " obtained" << endl;
            SetColor(7);
            Inventory.push_back(NewRing);
          } else {
            cout << "Room contained a ring. It turned to dust after first touch\n";
          }
          break;
        case 5:
          cout << "There is a demon sitting in a room. A red ring shine on his "
                  "finger. Ring Last Mage knew long ago\n";
          SetColor(4);
          cout << "- Hello there. Looks like i have a Mage here. Maybe i can "
                  "call guard... But i won't. Interested in deal? I can take "
                  "part of your health and create ring of your lifepower\n";
          SetColor(7);
          cout << "1. Accept a deal\n2. Reject the deal\n";
          switch (TakeInt(1,3)) {
            case 1:
              SetColor(4);
              cout << "- It's a pleasure working with Mage\n";
              SetColor(7);
              cout << "As Demon cast his spell, Last mage feel that he lost some of his health. Soon after demon give him a ring\n";
              SetColor(4);
              cout << "- Here you go. Good luck, Last Mage\n";
              SetColor(2);
              cout << "Revengeance ring obtained " << endl;
              SetColor(7);
              Inventory.push_back(NewRing);
              break;
            case 2:
              SetColor(4);
              cout << "- Well, bye then\n";
              SetColor(7);
              break;
          }
          break;
        case 6:
          cout << "There's cell with Mage skeleton. Last Mage can to give rest "
                  "to this Mage in cost of all Mana\n1. Do\n2. Go away";
          switch (TakeInt(1,2)) { 
            case 1:
              cout << "Last Mage use all of his Mana to release Mage soul. He "
                      "feel that his Mana limit changed";
              Mana = 0;
              ManaMax += 10;
              break;
            case 2:
              cout << "Last Mage go away";
              break;
          }
          break;
        case 7:
          cout << "Room was empty\n";
          break;
      }
      break;
  }
}

void DrawMap() { 
  for (int y = 0; y < Map.size(); y++) {
    for (int x = 0; x < Map[0].size(); x++) {
      if (CoordX == x and CoordY == y) {
        cout << "*" << Map[y][x].substr(1);
      } else {
        cout << Map[y][x];
      }
    }
    cout << endl;
  }
  int Deed = 2, Choice;
  cout << "S - Start E - Enemy P - Powerful enemy B - Boss M - Mana room R - Room\n";
  SetColor(11);
  cout << "\nLast Mage\n";
  SetColor(15);
  cout << "1. Inventory\n";
  if (Map[CoordY][CoordX].substr(1) == "-") {
    cout << Deed << ". Forward\n";
    Deed++;
  }
  if (Map[CoordY - 1][CoordX].substr(1) == "/") {
    cout << Deed << ". Left\n";
    Deed++;
  }
  if (Map[CoordY + 1][CoordX].substr(1,2) == "\\") {
    cout << Deed << ". Right\n";
    Deed++;
  }
  cin >> Choice;
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
    cout << "That didn't work\n";
  }
}

void InventoryChooser();
void Equipper();

void ShowRings() {
  cout << "0. Back\n";
  for (int i = 0; i < Inventory.size(); i++) {
    cout << i+1 << ". " << Inventory[i].Name;
    if (Inventory[i].Equipped) {
      cout << " - equipped";
    }
    cout << endl;
  }
  InventoryChooser();
  if (ChosenRing == 0) {
    return;
  }
  cout << "1. Description\n";
  if (ChosenRing->Equipped) {
    cout << "2. Unequip";
  } else {
    cout << "2. Equip";
  }
  cout << "\n3. Back\n";
  int Choose;
  cin >> Choose;
  switch (Choose) { 
    case 1:
      system("cls");
      cout << ChosenRing->Name << endl;
      cout << ChosenRing->Description << endl;
      break;
    case 2:
      if (ChosenRing->Equipped) {
        ChosenRing->Equipped = false;
        ChosenRing->AddRingEffect(-1, &MainHP, &MainHPMax, &Mana, &ManaMax,
                                  &SecondAtkChance, &DefaultDefence,
                                  &DefaultStatusMult, &SecondChance,
                                  &DefaultDamageMult);
        erase_if(Arm, [](const Ring& r) { return !r.Equipped; });
        system("cls");
        cout << "Uneqipped\n";
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
  cout << "Choose\n";
  int Chosen;
  bool flag = true;
  do {
    while (!(cin >> Chosen)) {
      cout << "Invalid ring\n";
    }
    if (Chosen == 0) {
      ChosenRing = 0;
      flag = false;
      State = 1;
      system("cls");
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Inventory.size())) {
        cout << "Invalid ring!\n";
      } else {
        ChosenRing = &Inventory[Chosen - 1];
        flag = false;
      }
    }
  } while (flag);
}

void Equipper() {
  cout << "0. Back\n";
  for (int i = 0; i < RingsMax; i++) {
    if (i < Arm.size()) {
      cout << i + 1 << ". " << Arm[i].Name << endl;
    } else {
      cout << i+1 << ". Empty\n";
      break;
    }
  }
  int Chosen, CurrSlot;
  bool flag = true;
  do {
    while (!(cin >> Chosen)) {
      cout << "Invalid slot\n";
    }
    if (Chosen == 0) {
      flag = false;
      system("cls");
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Arm.size()+1)) {
        cout << "Invalid slot!\n";
      } else {
        if (Chosen == Arm.size() + 1) {
          Arm.push_back(*ChosenRing);
          ChosenRing->Equipped = true;
          ChosenRing->AddRingEffect(1, &MainHP, &MainHPMax, &Mana, &ManaMax,
                                    &SecondAtkChance, &DefaultDefence,
                                    &DefaultStatusMult, &SecondChance,
                                    &DefaultDamageMult);
          system("cls");
          cout << "Equipped\n";
          return;
        } else {
          if (Arm[Chosen-1].Uneqippable) {
            Arm[Chosen - 1].Equipped = false;
            Arm[Chosen - 1].AddRingEffect(-1, &MainHP, &MainHPMax, &Mana,
                                          &ManaMax, &SecondAtkChance,
                                          &DefaultDefence, &DefaultStatusMult,
                                          &SecondChance, &DefaultDamageMult);
            erase_if(Arm, [](const Ring& r) { return !r.Equipped; });
            Arm.push_back(*ChosenRing);
            ChosenRing->Equipped = true;
            ChosenRing->AddRingEffect(1, &MainHP, &MainHPMax, &Mana, &ManaMax,
                                      &SecondAtkChance, &DefaultDefence,
                                      &DefaultStatusMult, &SecondChance,
                                      &DefaultDamageMult);
            system("cls");
            cout << "Equipped\n";
            return;
          } else {
            cout << "This ring is not removable";
          }
        }
        flag = false;
      }
    }
  } while (flag);
  
}

int main() {
  srand(time(NULL));
  SetColor(8);
  cout << "You are the Last Mage. \nYour goal is simple - revenge."
          "To revenge for all the order slayed - to destroy their mage "
          "slayers.\n";
  SetColor(4);
  cout << "Once and for all.\n\n";
  SetColor(7);
  CurrStage = MaxStage = 0;
  MainHP = MainHPMax = 100;
  Mana = ManaMax = 100;
  Defence = 1;
  State = 2;
  int Choice;
  Create_enemies();
  while (MainHP > 0) {
    switch (State) {
      case 1:
        DrawMap();
        break;
      case 2:
        do {
          int counter = 1;
          Defence = DefaultDefence;
          DamageMult = DefaultDamageMult;
          StatusMult = DefaultStatusMult;
          SetColor(4);
          cout << "\nEnemies\n";
          SetColor(7);
          for (Boss& boss : StageBosses) {
            cout << counter << ". ";
            counter++;
            boss.Stats(&Enemies);
          }
          for (Enemy& enemy : Enemies) {
            cout << counter << ". ";
            counter++;
            enemy.Stats(&Enemies);
          }
          SetColor(11);
          cout << "\nLast Mage\n";
          SetColor(15);
          cout << "Health: ";
          SetColor(4);
          cout << MainHP;
          SetColor(15);
          cout << " Mana: ";
          SetColor(3);
          cout << Mana << "\n";
          SetColor(15);
          cout << "1. Regenerate. Gain ";
          SetColor(3);
          cout << "15\n";
          SetColor(15);
          if (Mana >= 20) {
            cout
                << "2. Support with spell. ";
            SetColor(3);
            cout << "20\n";
            SetColor(15);
            cout << "3. Attack with one element. ";
            SetColor(3);
            cout << "20\n";
            SetColor(15);
            if (Mana >= 40) {
              cout << "4. Attack with two elements. ";
              SetColor(3);
              cout << "40\n";
              SetColor(15);
            }
          }
          SetColor(15);
          cin >> Choice;
          switch (Choice) {
            case 1:
              Mana = Clamp(Mana + 15, 0, ManaMax);
              system("cls");
              cout << "Last Mage started regenerating\n";
              break;
            case 2:
              if (Mana >= 20) {
                Mana -= 20;
                Offence();
              }
              break;
            case 3:
              if (Mana >= 20) {
                Mana -= 20;
                EnemyChooser();
                Magic();
              }
              break;
            case 4:
              if (Mana >= 40) {
                EnemyChooser();
                Mana -= 40;
                cout << "Choose catalyst\n";
                cout
                    << "1. Flame. Ignite element. Doesn't damage but increase "
                       "status much\n";
                cout
                    << "2. Frost. Break element. Increase damage and status\n";
                cout << "3. Dark. Nullify element. Doesn't create status but "
                        "make damage bigger\n";
                cout << "4. Psycho. Overload element. Deal low heal to enemy "
                        "but add large status\n";
                cin >> Choice;
                switch (Choice) {
                  case 1:
                    DamageMult *= 0;
                    StatusMult *= 3;
                    break;
                  case 2:
                    DamageMult *= 1.5;
                    StatusMult *= 1.5;
                    break;
                  case 3:
                    DamageMult *= 3;
                    StatusMult *= 0;
                    break;
                  case 4:
                    DamageMult *= -1;
                    StatusMult *= 4.5;
                    break;
                  default:
                    system("cls");
                    cout << "That didn't work\n";
                    break;
                    break;
                }
                Magic();
              }
              break;
            default:
              system("cls");
              cout << "That didn't work\n";
              break;
          }
          if (rand() % 101 >= SecondAtkChance) {
            for (Enemy& enemy : Enemies) {
              enemy.Act(&MainHP, &Defence, &Enemies);
            }
            for (Boss& boss : StageBosses) {
              boss.Act(&Defence, &NormalAdd, &MainHP, &MaxEnemies, &StageBosses,
                       &Enemies, &MaxStage, &CurrStage, &CoordX, &CoordY,
                       &EliteAdd, &EliteRand, &CoordY, &GetableRings,
                       &Inventory, &Map);
            }
            if (MainHP <= 0) {
              if (SecondChance > 0) {
                SecondChance--;
                MainHP = 1;
                cout << "\nMage refused to fall.\n";
              } else {
                SetColor(4);
                cout << "\nThe Last Mage fell.\n\n";
                SetColor(15);
                exit(0);
              }
            }
          }
          Mana = Clamp(Mana + 15, 0, ManaMax);
          for (Ring& currRing : Arm) {
            currRing.RingAct(&MainHP, &MainHPMax, &Mana, &ManaMax);
          }
        } while (not StageBosses.empty() or not Enemies.empty());
        State = 1;
        break;
      case 3:
        ShowRings();
        break;
    }
  }
}