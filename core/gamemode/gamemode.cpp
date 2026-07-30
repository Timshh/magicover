#include "gamemode.h"

Gamemode::Gamemode()
    : Player(Manager.GetCreature("Last Mage"), &Teammates, &Render,
             &GlobalRenderer),
      GMBattle(&Render, &GlobalRenderer, &Teammates, &Enemies, &StageBosses,
               &Player, &CurrStage, &MaxEnemies, &Manager),
      GMMap(&Render),
      GMInventory(&Render, &Player, &GetableRings, &Manager),
      Manager(ResourceManager("data/creatures.json",
      "data/rings.json")){
  Teammates.push_back(&Player);
}

void Gamemode::Gameloop() {
  Render.PrintMessage(
      8,
      "You are the Last Mage. \nYour goal is simple - revenge."
      "To revenge for all the order slayed - to destroy their mage "
      "slayers.\n");
  Render.PrintMessage(4, "Once and for all.\n\n");
  GMBattle.CreateBoss();

  while (Player.Params.HP > 0) {
    switch (State) {
      case GMStates::Map:
        LocationAct(GMMap.MapAct());
        break;
      case GMStates::Battle:
        GMBattle.StartBattle();
        State = GMStates::Map;
        break;
      case GMStates::Inventory:
        if (GMInventory.ShowRings()) {
          State = GMStates::Map;
        }
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

void Gamemode::ChangeStage() {
  switch (CurrStage) {
    case 0:
      Render.PrintMessage(15, "Axe guardian ring shines bright\n");
      Render.PrintMessage(2, "Ring of memories obtained\n\n");
      Player.Inventory.push_back(
          Ring(Manager.GetRing("Ring of memories"), &Player));
      Render.PrintMessage(7, "Spacious outer palaces look regular");

      CoordX = 0, CoordY = 3;
      NormalEnemies = {"Hunter", "Warrior student", "Knight",
                       "Demon",  "Pseudo-Witch",    "Pseudo-Mage"};
      EliteEnemies = {"Archer", "Draconic hunter"};
      GMMap.CreateMap();
      break;
    case 1:
      Render.PrintMessage(15, "Ring shines in the dust\n");
      Render.PrintMessage(2, "Ring of arms obtained\n\n");
      Player.Inventory.push_back(
          Ring(Manager.GetRing("Ring of arms"), &Player));
      Render.PrintMessage(7, "Grandiose inner palaces shine before Last Mage");

      CoordX = 0, CoordY = 7;
      NormalEnemies = {"Demon", "Pseudo-Witch", "Pseudo-Mage",
                       "Automaton-Cleaner", "Automaton-Dog"};
      EliteEnemies = {"Automaton-Hunter", "Armored knight"};
      GetableRings.push_back("Thorn ring");
      GetableRings.push_back("Light ring");
      GetableRings.push_back("Light ring");
      GetableRings.push_back("Glass ring");
      GMMap.CreateMap();
      break;
    case 2:
      Render.PrintMessage(12, "- Overheat! Overheat! Overheat...\n");
      Render.PrintMessage(
          7, "As machine turned off, its chest opened. Inside was a ring\n");
      Render.PrintMessage(2, "Clockwork ring obtained\n\n");
      Player.Inventory.push_back(
          Ring(Manager.GetRing("Clockwork ring"), &Player));
      Render.PrintMessage(
          7, "Slayers section feels majestically. Soon it will burn");

      CoordX = 0, CoordY = 5;
      NormalEnemies = {"Pseudo-Witch",  "Pseudo-Mage",     "Automaton-Cleaner",
                       "Automaton-Dog", "Witch candidate", "Automaton-Dragon"};
      EliteEnemies = {"Slayer candidate", "Slayer"};
      GetableRings.push_back("Unstable ring");
      GetableRings.push_back("Dice ring");
      GMMap.CreateMap();
      break;
    case 3:
      Render.PrintMessage(
          10,
          "\nYou finished the mission - you destroyed the order's core\n"
          "Congratulations, Last Mage\n\n\n");
      exit(0);
  }
  MaxStage += 1;
  CurrStage += 1;
}

void Gamemode::LocationAct(int roomType) {
  Render.CleanRender();
  switch (roomType) {
    case -1:
      break;
    case 0:
      State = GMStates::Inventory;
      break;
    case 1:
      GMBattle.CreateBoss();
      State = GMStates::Battle;
      break;
    case 2:
      Render.PrintMessage(4, "Enemy appears\n");
      Enemies.push_back(new Enemy(
          Manager.GetCreature(NormalEnemies[rand() % NormalEnemies.size()]),
          &Enemies, &Render, &GlobalRenderer));
      State = GMStates::Battle;
      break;
    case 3:
      Render.PrintMessage(4, "Powerful enemy appears\n");
      Enemies.push_back(new Enemy(
          Manager.GetCreature(EliteEnemies[rand() % EliteEnemies.size()]),
          &Enemies, &Render, &GlobalRenderer));
      State = GMStates::Battle;
      break;
    case 4:
      Render.PrintMessage(15, "Last mage regenerate Health and Mana\n");
      Player.Params.HP = Player.Params.HPMax;
      Player.Params.Mana = Player.Params.ManaMax;
      break;
    case 5:
      int RoomType = rand() % 7 + 1;
      switch (RoomType) {
        case 1:
          Render.PrintMessage(4, "Slayer students attack Last Mage\n");
          for (int i = 0; i < (rand() % 2 + 4); i++) {
            Enemies.push_back(new Enemy(Manager.GetCreature("Warrior student"),
                                        &Enemies, &Render, &GlobalRenderer));
          }
          State = GMStates::Battle;
          break;
        case 2:
          Render.PrintMessage(
              15,
              "Room have a trap\n1. Go away\n2. Get the ring in the trap\n");
          switch (TakeInt(1, 2)) {
            case 1:
              Render.PrintMessage(15, "That was a good choice\n");
              break;
            case 2:
              int TrapDmg = rand() % 10 + 5;
              Player.Params.HP -= TrapDmg;
              if (GMInventory.NewRingChooser()) {
                Render.PrintMessage(15, "Last Mage took a ring in cost of ");
                Render.PrintMessage(15, TrapDmg, "\n");
                Render.PrintMessage(2, GMInventory.NewRing->Stats.Name,
                                    " obtained", "\n");
                Player.Inventory.push_back(*GMInventory.NewRing);
              } else {
                Render.PrintMessage(
                    15,
                    "Ring were a mirage, part of trap. Last Mage were "
                    "damaged by ");
                Render.PrintMessage(15, TrapDmg);
              }
          }
          break;
        case 3:
          Render.PrintMessage(4, "Ambush!\n");
          Enemies.push_back(new Enemy(Manager.GetCreature(EliteEnemies[0]),
                                      &Enemies, &Render, &GlobalRenderer));
          Enemies.push_back(new Enemy(Manager.GetCreature(NormalEnemies[0]),
                                      &Enemies, &Render, &GlobalRenderer));
          State = GMStates::Battle;
          break;
        case 4:
          if (GMInventory.NewRingChooser()) {
            Render.PrintMessage(15, "Room contained a ring\n");
            Render.PrintMessage(15, GMInventory.NewRing->Stats.Name,
                                " obtained", "\n");
            Player.Inventory.push_back(*GMInventory.NewRing);
          } else {
            Render.PrintMessage(
                15, "Room contained a ring. It turned to dust after touch\n");
          }
          break;
        case 5:
          Render.PrintMessage(
              15,
              "There is a demon sitting in a room. A red ring shine on his "
              "finger. Ring Last Mage knew long ago\n");
          Render.PrintMessage(
              15,
              "- Hello there. Looks like i have a Mage here. Maybe i can "
              "call guard... But i won't. Interested in deal? I can take "
              "part of your health and create ring of your lifepower\n");
          Render.PrintMessage(7, "1. Accept a deal\n2. Reject the deal\n");
          switch (TakeInt(1, 2)) {
            case 1:
              Render.PrintMessage(4, "- It's a pleasure working with Mage\n");
              Render.PrintMessage(
                  7,
                  "As Demon cast his spell, Last mage feel that he lost "
                  "some of his health. Soon after demon give him a ring\n");
              Render.PrintMessage(4, "- Here you go. Good luck, Last Mage\n");
              Render.PrintMessage(2, "Revengeance ring obtained ", "\n");
              Player.Inventory.push_back(*GMInventory.NewRing);
              break;
            case 2:
              Render.PrintMessage(4, "- Well, bye then\n");
              break;
          }
          break;
        case 6:
          Render.PrintMessage(
              15,
              "There's cell with Mage skeleton. Last Mage can to give rest "
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