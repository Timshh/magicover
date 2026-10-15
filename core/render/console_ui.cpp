#include "console_ui.h"

ConsoleUI::ConsoleUI() : UIController(), game_(Core()) {
  game_.AddUI(this);
  game_.StartGame();
}

void ConsoleUI::SetColor(const int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void ConsoleUI::CleanRender() { system("cls"); }

void ConsoleUI::Battle() {
  std::vector<BattleActions> battleActions;
  PrintMessage(7, "enemies\n");
  for (int i = 1; i <= game_.gm_battle.enemies.size(); i++) {
    Creature* enemy = game_.gm_battle.enemies[i - 1];
    PrintMessage(7, i, ". ");
    if (enemy->alive) {
      if (enemy->params.hp >= enemy->params.hp_max / 2) {
        PrintMessage(15, enemy->params.calm_text);
      } else {
        if (enemy->params.hp >= enemy->params.hp_max / 4) {
          PrintMessage(15, enemy->params.hurt_text);
        } else {
          PrintMessage(15, enemy->params.damaged_text);
        }
      }
      PrintMessage(12, " ", enemy->params.flame);
      PrintMessage(11, " ", enemy->params.frost);
      PrintMessage(8, " ", enemy->params.dark);
      PrintMessage(13, " ", enemy->params.psycho);
      PrintMessage(7, "\n");
    } else {
      PrintMessage(15, enemy->params.name, ", dead\n");
    }
  }
  int additionalSize = game_.gm_battle.enemies.size();
  for (int i = 1; i <= game_.gm_battle.stage_bosses.size(); i++) {
    Creature* enemy = game_.gm_battle.stage_bosses[i - 1];
    PrintMessage(7, i + additionalSize, ". ");
    if (enemy->alive) {
      if (enemy->params.hp >= enemy->params.hp_max / 2) {
        PrintMessage(15, enemy->params.calm_text);
      } else {
        if (enemy->params.hp >= enemy->params.hp_max / 4) {
          PrintMessage(15, enemy->params.hurt_text);
        } else {
          PrintMessage(15, enemy->params.damaged_text);
        }
      }
      PrintMessage(12, " ", enemy->params.flame);
      PrintMessage(11, " ", enemy->params.frost);
      PrintMessage(8, " ", enemy->params.dark);
      PrintMessage(13, " ", enemy->params.psycho);
      PrintMessage(7, "\n");
    } else {
      PrintMessage(15, enemy->params.name, ", dead\n");
    }
  }
  PrintMessage(11, "\nLast Mage\n");
  PrintMessage(15, "Health: ");
  PrintMessage(4, game_.player.params.hp);
  PrintMessage(15, " mana: ");
  PrintMessage(3, game_.player.params.mana, "\n");
  PrintMessage(10, game_.player.params.poison, " ");
  PrintMessage(9, game_.player.params.disease, " ");
  PrintMessage(8, game_.player.params.mechanization, " ");
  PrintMessage(12, game_.player.params.stealer, "\n");
  battleActions = game_.BattleGetActions();
  for (int i = 1; i <= battleActions.size(); i++) {
    switch (battleActions[i - 1]) {
      case BattleActions::Regenerate:
        PrintMessage(15, std::to_string(i) + ". Regenerate. Gain ");
        PrintMessage(3, "15\n");
        break;
      case BattleActions::SupportSpell:
        PrintMessage(15, "2. Support with spell. ");
        PrintMessage(3, "20\n");
        break;
      case BattleActions::Spell:
        PrintMessage(15, "3. Attack with one element. ");
        PrintMessage(3, "20\n");
        break;
      case BattleActions::PowerfulSpell:
        PrintMessage(15, "4. Attack with two elements. ");
        PrintMessage(3, "40\n");
    }
  }
  PrintMessage(7, "\nChoose\n");
  int choice;
  int spell;
  Creature* target;
  choice = TakeInt(1, battleActions.size());
  switch (battleActions[choice - 1]) {
    case BattleActions::Regenerate:
      game_.BattleAct(BattleActions::Regenerate);
      break;

    case BattleActions::SupportSpell:
      PrintMessage(15, "Choose spell:\n");
      PrintMessage(15, "1. Steel blood. Decrease incoming damage by half\n");
      PrintMessage(15, "2. Blue heart. Heal ");
      PrintMessage(4, "50\n");
      PrintMessage(15, "3. Radiance. Heal ");
      PrintMessage(4, "80");
      PrintMessage(15, " but incoming damage rise by half\n");
      game_.BattleAct(BattleActions::SupportSpell, TakeInt(1, 4));
      break;

    case BattleActions::Spell:
      PrintMessage(15, "Select enemy\n");
      target = SelectTarget();
      PrintMessage(15,
                   "Choose element:\n1. flame. Burn enemy "
                   "slowly\n2. frost. Make enemy "
                   "attacks weaker\n3. dark. With darken mind "
                   "enemy may miss\n4. psycho. "
                   "Enemy may lose control and attack self\n");
      game_.BattleAct(BattleActions::Spell, TakeInt(1, 4), target);
      break;

    case BattleActions::PowerfulSpell:
      PrintMessage(15, "Select enemy\n");
      target = SelectTarget();
      PrintMessage(
          15,
          "Choose catalyst\n1. flame. Ignite element. Doesn't damage but "
          "increase status much\n2. frost. Break element. Increase "
          "damage and "
          "status\n3. dark. Nullify element. Doesn't create status but "
          "make damage bigger\n4. psycho. Overload element. Deal low "
          "heal to enemy but add large status\n");
      spell = TakeInt(1, 4);
      PrintMessage(15,
                   "Choose element:\n1. flame. Burn enemy "
                   "slowly\n2. frost. Make enemy "
                   "attacks weaker\n3. dark. With darken mind "
                   "enemy may miss\n4. psycho. "
                   "Enemy may lose control and attack self\n");
      game_.BattleAct(BattleActions::PowerfulSpell, spell, target,
                     TakeInt(1, 4));
      break;
  }
}

void ConsoleUI::Map() {
  std::vector<int> newWays;
  PrintMessage(15, "0. Inventory\n");
  newWays = game_.gm_map.GetWays();
  for (int i = 1; i <= newWays.size(); i++) {
    int currNode = game_.gm_map.GetNodeType(newWays[i - 1]);
    PrintMessage(15, std::to_string(i) + ". ");
    switch (currNode) {
      case 1:
        PrintMessage(15, "Boss");
        break;
      case 2:
        PrintMessage(15, "Room with enemies");
        break;
      case 3:
        PrintMessage(15, "Room with powerful enemies");
        break;
      case 4:
        PrintMessage(15, "mana Room");
        break;
      case 5:
        PrintMessage(15, "Unknown Room");
        break;
    }
    PrintMessage(15, "\n");
  }
  PrintMessage(7, "\nChoose\n");
  int choice = TakeInt(0, newWays.size());
  CleanRender();
  if (choice != 0) {
    game_.MapChooseRoom(newWays.at(choice - 1));
  } else {
    game_.state = GMStates::kInventory;
  }
}

void ConsoleUI::Inventory() {
  PrintMessage(15, "0. Return\n");
  Ring* currRing;
  for (int i = 1; i <= game_.player.inventory.size(); i++) {
    currRing = &game_.player.inventory[i - 1];
    PrintMessage(15, std::to_string(i), ". ", currRing->stats.name);
    if (currRing->stats.equipped) {
      PrintMessage(15, " - equipped");
    }
    PrintMessage(15, "\n");
  }
  PrintMessage(7, "\nChoose\n");
  int choice = TakeInt(0, game_.player.inventory.size());
  CleanRender();
  if (choice != 0) {
    currRing = &game_.player.inventory[choice - 1];
    PrintMessage(15, "0. Back\n");
    PrintMessage(15, "1. Description\n");
    if (currRing->stats.equipped) {
      PrintMessage(15, "2. Unequip");
    } else {
      PrintMessage(15, "2. Equip");
    }
    PrintMessage(7, "\nChoose\n");
    int Choose;
    std::cin >> Choose;
    switch (Choose) {
      case 0:
        return;
      case 1:
        CleanRender();
        PrintMessage(15, currRing->stats.name, "\n");
        PrintMessage(15, currRing->stats.description, "\n");
        break;
      case 2:
        if (currRing->stats.equipped) {
          currRing->stats.equipped = false;
          currRing->AddRingEffect(true);
          erase_if(game_.player.arm,
                   [](const Ring& r) { return !r.stats.equipped; });
          CleanRender();
          PrintMessage(15, "Uneqipped\n");
        } else {
          PrintMessage(15, "0. Back\n");
          for (int i = 0; i < game_.player.params.rings_max; i++) {
            if (i < game_.player.arm.size()) {
              PrintMessage(15, i + 1, ". ", game_.player.arm[i].stats.name,
                           "\n");
            } else {
              PrintMessage(15, i + 1, ". Empty finger\n");
              break;
            }
          }
          PrintMessage(7, "\nChoose\n");
          choice = TakeInt(0, game_.player.arm.size() + 1);
          if (choice != 0) {
            if (choice == game_.player.arm.size() + 1) {
              game_.player.arm.push_back(*currRing);
              currRing->stats.equipped = true;
              currRing->AddRingEffect(true);
              CleanRender();
              PrintMessage(15, "equipped\n");
              return;
            } else {
              if (game_.player.arm[choice - 1].stats.uneqippable) {
                game_.player.arm[choice - 1].stats.equipped = false;
                game_.player.arm[choice - 1].AddRingEffect(false);
                erase_if(game_.player.arm,
                         [](const Ring& r) { return !r.stats.equipped; });
                game_.player.arm.push_back(*currRing);
                currRing->stats.equipped = true;
                currRing->AddRingEffect(true);
                CleanRender();
                PrintMessage(15, "equipped\n");
                return;
              } else {
                PrintMessage(15, "This ring is not removable");
              }
            }
          }
        }
    }
  } else {
    game_.state = GMStates::kMap;
  }
}

void ConsoleUI::Room() {
  if (game_.RoomGetActions() != 0) {
    PrintMessage(7, "\nChoose\n");
    int choice = TakeInt(0, game_.RoomGetActions());
    CleanRender();
    game_.RoomAct(choice);
  } else {
    PrintMessage(7, "\n1. Continue\n");
    int choice = TakeInt(1, 1);
    CleanRender();
    game_.state = GMStates::kMap;
  }
}

void ConsoleUI::Run() {
  while (game_.player.alive) {
    switch (game_.state) {
      case GMStates::kBattle:
        Battle();
        break;
      case GMStates::kInventory:
        Inventory();
        break;
      case GMStates::kMap:
        Map();
        break;
      case GMStates::kRoom:
        Room();
        break;
    }
  }
}

void ConsoleUI::CallAct(const RenderActions action, const int ID,
                        const int params,
                        const int subparams) {
  Creature* target;
  if (ID != -2) {
    if (ID == -1) {
      target = &game_.player;
    } else {
      if (ID >= 10000) {
        target = game_.gm_battle.stage_bosses[ID - 10000];
      } else {
        target = game_.gm_battle.enemies[ID];
      }
    }
  }
  switch (action) {
    case RenderActions::kAttack:
      PrintMessage(
          15, target->params.atk_texts[rand() % target->params.atk_texts.size()],
          "\n");
      break;

    case RenderActions::kNewRing:
      PrintMessage(
          2,
          game_.player.inventory.at(game_.player.inventory.size() - 1).stats.name,
          " obtained\n");
      break;

    case RenderActions::kRoomAct:
      switch (params) {
        case 1:
          PrintMessage(15, "Slayer students attack Last Mage\n");
          break;
        case 2:
          switch (subparams) {
            case 0:
              PrintMessage(15,
                           "Room have a trap\n1. Go away\n2. Get the ring in "
                           "the trap\n");
              break;
            case 1:
              PrintMessage(15, "That was a good choice\n");
              break;
            case 2:
              break;
            case 3:
              PrintMessage(15, "Ring were a mirage, part of trap\n");
              break;
          }

          break;
        case 3:
          PrintMessage(15, "Ambush!\n");
          break;
        case 5:
          PrintMessage(15, "Room contained a ring. ");
          switch (subparams) {
            case 1:
              PrintMessage(15, "\n");
              break;
            case 2:
              PrintMessage(15, "It turned into dust after a touch\n");
              break;
          }
          break;
        case 4:
          switch (subparams) {
            case 0:
              PrintMessage(
                  15,
                  "There is a demon sitting in a room. A red ring shine on his "
                  "finger. Ring Last Mage knew long ago\n");
              PrintMessage(
                  15,
                  "- Hello there. Looks like i have a Mage here. Maybe i can "
                  "call guard... But i won't. Interested in deal? I can take "
                  "part of your health and create ring of your lifepower\n");
              PrintMessage(7, "1. Accept the deal\n2. Reject the deal\n");
              break;
            case 1:
              PrintMessage(4, "- It's a pleasure to work with a Mage\n");
              PrintMessage(
                  7,
                  "As Demon cast his spell, Last mage feel that he lost "
                  "some of his health. Soon after demon give him a ring\n");
              PrintMessage(4, "- Here you go. Good luck, Last Mage\n");
              PrintMessage(2, "Revengeance ring obtained ", "\n");
              break;
            case 2:
              PrintMessage(4, "- Well, bye then\n");
              break;
          }
          break;
        case 6:
          switch (subparams) {
            case 0:
              PrintMessage(
                  15,
                  "There's cell with Mage skeleton. Last Mage can to give rest "
                  "to this Mage in cost of all mana\n1. Do\n2. Go away\n");
              break;
            case 1:
              PrintMessage(
                  15,
                  "Last Mage use all of his mana to release Mage soul. He "
                  "feel that his mana limit changed");
              break;
            case 2:
              PrintMessage(15, "Last Mage go away");
              break;
          }

          break;
        case 7:
          PrintMessage(15, "Room was empty\n");
          break;
      }
      break;

    case RenderActions::kGameStart:
      PrintMessage(
          8,
          "You are the Last Mage. \nYour goal is simple - revenge."
          "To revenge for all the order slayed - to destroy their mage "
          "slayers\n");
      PrintMessage(4, "Once and for all.\n\n");
      break;

    case RenderActions::kStageChange:
      switch (params) {
        case 0:
          PrintMessage(15, "Axe guardian ring shines bright\n");
          PrintMessage(2, "Ring of memories obtained\n\n");
          PrintMessage(7, "Spacious outer palaces look regular\n");
          break;
        case 1:
          PrintMessage(15, "Ring shines in the dust\n");
          PrintMessage(2, "Ring of arms obtained\n\n");
          PrintMessage(7, "Grandiose inner palaces shine before Last Mage\n");
          break;
        case 2:
          PrintMessage(12, "- Overheat! Overheat! Overheat...\n");
          PrintMessage(
              7,
              "As machine turned off, its chest opened. Inside was a ring\n");
          PrintMessage(2, "Clockwork ring obtained\n\n");
          PrintMessage(
              7, "Slayers section feels majestically. Soon it will burn\n");
          break;
        case 3:
          PrintMessage(
              10,
              "\nYou finished the mission - you destroyed the order's core\n"
              "Congratulations, Last Mage\n\n\n");
      }
      break;

    case RenderActions::kBattleEnd:
      PrintMessage(6, "\nBattle is over\n");
      game_.BattleFinish();
      break;

    case RenderActions::kRegen:
      CleanRender();
      PrintMessage(15, "Last Mage started regeneration\n");
      break;

    case RenderActions::kSupportSpell:
      switch (params) {
        case 1:
          CleanRender();
          PrintMessage(15, "Last Mage blood became gray. His protction rise\n");
          break;
        case 2:
          CleanRender();
          PrintMessage(15,
                       "Last Mage heart beat strong and slow, "
                       "regenerating his health\n");
          break;
        case 3:
          CleanRender();
          PrintMessage(15,
                       "Last Mage heart glow inside his chest, refilling his "
                       "health. He "
                       "is vulnerable now\n");
          break;
      }
      break;

    case RenderActions::kSpell:
      switch (params) {
        case 1:
          CleanRender();
          PrintMessage(15, "Last Mage cast fireball\n");
          break;
        case 2:
          CleanRender();
          PrintMessage(15, "Last Mage throw ice arrow\n");
          break;
        case 3:
          CleanRender();
          PrintMessage(15, "Last Mage cast dark smoke\n");
          break;
        case 4:
          CleanRender();
          PrintMessage(15, "Last Mage cast cast paranoia\n");
          break;
      }
      break;

    case RenderActions::kPowerfulSpell:
      switch (params) {
        case 1:
          CleanRender();
          PrintMessage(15, "Last Mage cast fire wall\n");
          break;
        case 2:
          CleanRender();
          PrintMessage(15, "Last Mage shoot ice spikes\n");
          break;
        case 3:
          CleanRender();
          PrintMessage(15, "Last Mage cast pure darkness\n");
          break;
        case 4:
          CleanRender();
          PrintMessage(15, "Last Mage cast cast hypnosis\n");
          break;
      }
      break;

    case RenderActions::kTakedamage:
      PrintMessage(15, target->params.name, " recieved ", params, " damage\n");
      break;

    case RenderActions::kSpecialAttack:
      switch (target->params.spec_atk_id) {
        case 1:
          PrintMessage(
              15, "Shield guardian used heal potion - restored 20 health\n");
          break;
        case 2:
          PrintMessage(15,
                       "Axe guardian looked at ring on his arm. His "
                       "elemental statuses "
                       "decreased slightly\n");
          break;
        case 3:

          if (params == 0) {
            PrintMessage(15, "Witch created cluster of arms\n");
          } else {
            PrintMessage(
                15,
                "Witch tried to create more arms but overloaded herself - 20 "
                "damage\n");
          }
          break;
        case 4:
          PrintMessage(15, "Golem releases steam\n");
          PrintMessage(12, "- Overheat. Processing...\n");
          break;
        case 5:
          std::cout,
              "Wings throw feathers around. Feathers decrease enemy "
              "statuses\n";
          break;
        case 6:
          PrintMessage(
              15, "Tyrant emits a mighty roar and strike with all limbs\n");
          break;
        case 7:
          PrintMessage(
              15,
              "Halo shine with purple light. Light heal all enemies by 20 "
              "health\n");
          break;
      }
      break;

    case RenderActions::kDeath:
      if (ID == -1) {
        PrintMessage(15, "Last Mage fell\n\n");
      } else {
        PrintMessage(15, target->params.death_text, "\n");
      }
      break;

    case RenderActions::kAtkPreparing:
      switch (target->params.spec_atk_id) {
        case 6:
          PrintMessage(15, "Tyrant prepares something, her core glow bright\n");
          break;
      }
      break;

    case RenderActions::kOverload:
      switch (params) {
        case 1:
          PrintMessage(15, "flame overload! ", target->params.name,
                       " exploded");
          break;
        case 2:
          PrintMessage(15, "frost overload! ", target->params.name,
                       " were frozen");
          break;
        case 3:
          PrintMessage(15, "dark overload! ", target->params.name,
                       " got corrupted");
          break;
        case 4:
          PrintMessage(15, "psycho overload! ", target->params.name,
                       " attacked self in hysteria");
          break;
      }
      PrintMessage(15, "\n");
      break;

    case RenderActions::kAppear:
      switch (target->params.spec_atk_id) {
        case 1:
          PrintMessage(8,
                       "Two guardians of castle stand before Last Mage. "
                       "One raise his "
                       "heavy shield, another prepared "
                       "battle axe. Fight is only "
                       "option\n");
          break;
        case 3:
          PrintMessage(
              8,
              "The palace smell dry. In center of it stands mummified "
              "witch "
              "corpse with eight arms. As Mage get closer she rise her "
              "gaze "
              "to "
              "Last Mage, her dead eyes glow red. This is mad witch who "
              "cheated death now known as ");
          PrintMessage(4, "InfarmY");
          PrintMessage(8, " - supreme ripper\n");
          break;
        case 4:
          PrintMessage(8,
                       "As Last Mage enter the palace, smoke fill it. As "
                       "steam cleared, "
                       "Gorgeous machine stood before Last Mage. ");
          PrintMessage(14, "GO-13M. Greatest clockwork mechanism.");
          PrintMessage(
              8, " It's a pity that such perfection is enemy of the Mage\n");
          PrintMessage(12, "- Powerful threat detected. Starting battle\n ");
          break;
        case 6:
          PrintMessage(
              8,
              "Gorgeous creature were watching in mosaic window as Last "
              "Mage "
              "appeared. It slowly turns to manifest itself. Thin legs "
              "levitate "
              "above ground, Halo shines with purple, Wings spread wide "
              "and "
              "separate from body, long "
              "tail curl around thin arm and purple core shine inside its "
              "chest. Round dark helmet hide its head. Creature look too "
              "weird "
              "to be a human. This is the final battle. Battle with\n");
          PrintMessage(13, "TYRANT");
          PrintMessage(8, " - the order creator and the first slayer\n");
          break;
      }
  }
}

int ConsoleUI::TakeInt(const int min, const int max) {
  int choice;
  do {
    while (!(std::cin >> choice)) {
      PrintMessage(4, "Invalid choice\n");
      std::cin.clear();
      std::cin.ignore();
    }
    if ((choice < min) or (choice > max)) {
      PrintMessage(4, "Invalid choice!\n");
      std::cin.clear();
      std::cin.ignore();
    } else {
      return choice;
    }
  } while (true);
}

Creature* ConsoleUI::SelectTarget() {
  int size = game_.gm_battle.enemies.size() + game_.gm_battle.stage_bosses.size();
  int choice = TakeInt(1, size) - 1;
  if (choice < game_.gm_battle.enemies.size()) {
    return game_.gm_battle.enemies[choice];
  } else {
    return game_.gm_battle.stage_bosses[choice - game_.gm_battle.enemies.size()];
  }
}