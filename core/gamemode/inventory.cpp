#include "inventory.h"

Inventory::Inventory(ConsoleRenderer* const render, Mage* const player,
                     std::vector<std::string>* const getableRings,
                     ResourceManager* const manager)
    : Render(render), Player(player), GetableRings(getableRings), Manager(manager)  {}

bool Inventory::NewRingChooser() {
  if (GetableRings->empty()) {
    return false;
  } else {
    int ID = rand() % GetableRings->size();
    NewRing = new Ring(Manager->GetRing(GetableRings->at(ID)), Player);
    erase(*GetableRings, GetableRings->at(ID));
    return true;
  }
  return true;
}

bool Inventory::ShowRings() {
  Render->PrintMessage(15, "0. Back\n");
  for (int i = 0; i < Player->Inventory.size(); i++) {
    Render->PrintMessage(15, i + 1, ". ", Player->Inventory[i].Stats.Name);
    if (Player->Inventory[i].Stats.Equipped) {
      Render->PrintMessage(15, " - equipped");
    }
    Render->PrintMessage(15, "\n");
  }
  if (InventoryChooser()) {
    return true;
  }
  if (ChosenRing == nullptr) {
    return false;
  }
  Render->PrintMessage(15, "1. Description\n");
  if (ChosenRing->Stats.Equipped) {
    Render->PrintMessage(15, "2. Unequip");
  } else {
    Render->PrintMessage(15, "2. Equip");
  }
  Render->PrintMessage(15, "\n3. Back\n");
  int Choose;
  std::cin >> Choose;
  switch (Choose) {
    case 1:
      Render->CleanRender();
      Render->PrintMessage(15, ChosenRing->Stats.Name, "\n");
      Render->PrintMessage(15, ChosenRing->Stats.Description, "\n");
      break;
    case 2:
      if (ChosenRing->Stats.Equipped) {
        ChosenRing->Stats.Equipped = false;
        ChosenRing->AddRingEffect(true);
        erase_if(Player->Arm, [](const Ring& r) { return !r.Stats.Equipped; });
        Render->CleanRender();
        Render->PrintMessage(15, "Uneqipped\n");
      } else {
        Equipper();
      }
      break;
    default:
      Render->CleanRender();
      break;
  }
  return false;
}

bool Inventory::InventoryChooser() {
  Render->PrintMessage(15, "Choose\n");
  int Chosen;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      Render->PrintMessage(15, "Invalid ring\n");
    }
    if (Chosen == 0) {
      ChosenRing = 0;
      flag = false;
      return true;
      Render->CleanRender();
      return false;
    } else {
      if ((Chosen < 1) or Chosen > (Player->Inventory.size())) {
        Render->PrintMessage(15, "Invalid ring!\n");
      } else {
        ChosenRing = &Player->Inventory[Chosen - 1];
        flag = false;
      }
    }
  } while (flag);
  return false;
}

void Inventory::Equipper() {
  Render->PrintMessage(15, "0. Back\n");
  for (int i = 0; i < Player->Params.RingsMax; i++) {
    if (i < Player->Arm.size()) {
      Render->PrintMessage(15, i + 1, ". ", Player->Arm[i].Stats.Name, "\n");
    } else {
      Render->PrintMessage(15, i + 1, ". Empty finger\n");
      break;
    }
  }
  int Chosen, CurrSlot;
  bool flag = true;
  do {
    while (!(std::cin >> Chosen)) {
      Render->PrintMessage(15, "Invalid slot\n");
      Render->CleanRender();
    }
    if (Chosen == 0) {
      flag = false;
      Render->CleanRender();
      return;
    } else {
      if ((Chosen < 1) or Chosen > (Player->Params.RingsMax)) {
        Render->PrintMessage(15, "Invalid slot!\n");
      } else {
        if (Chosen == Player->Arm.size() + 1) {
          Player->Arm.push_back(*ChosenRing);
          ChosenRing->Stats.Equipped = true;
          ChosenRing->AddRingEffect(true);
          Render->CleanRender();
          Render->PrintMessage(15, "Equipped\n");
          return;
        } else {
          if (Player->Arm[Chosen - 1].Stats.Uneqippable) {
            Player->Arm[Chosen - 1].Stats.Equipped = false;
            Player->Arm[Chosen - 1].AddRingEffect(false);
            erase_if(Player->Arm,
                     [](const Ring& r) { return !r.Stats.Equipped; });
            Player->Arm.push_back(*ChosenRing);
            ChosenRing->Stats.Equipped = true;
            ChosenRing->AddRingEffect(true);
            Render->CleanRender();
            Render->PrintMessage(15, "Equipped\n");
            return;
          } else {
            Render->PrintMessage(15, "This ring is not removable");
          }
        }
        flag = false;
      }
    }
  } while (flag);
}