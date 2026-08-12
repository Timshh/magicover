#include "consoleUI.h"

ConsoleUI::ConsoleUI() : UIController(), Game(Core()) {
  Game.AddUI(this);
  Game.StartGame();
}

void ConsoleUI::SetColor(int const color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void ConsoleUI::CleanRender() { system("cls"); }

void ConsoleUI::Battle() {
  std::vector<BattleActions> battleActions;
  PrintMessage(7, "Enemies\n");
  for (int i = 1; i <= Game.GMBattle.Enemies.size(); i++) {
    Creature* enemy = Game.GMBattle.Enemies[i - 1];
    PrintMessage(7, i, ". ");
    if (enemy->Alive) {
      if (enemy->Params.HP >= enemy->Params.HPMax / 2) {
        PrintMessage(15, enemy->Params.CalmText);
      } else {
        if (enemy->Params.HP >= enemy->Params.HPMax / 4) {
          PrintMessage(15, enemy->Params.HurtText);
        } else {
          PrintMessage(15, enemy->Params.DamagedText);
        }
      }
    } else {
      PrintMessage(15, enemy->Params.Name, ", dead");
    }

    PrintMessage(12, " ", enemy->Params.Flame);
    PrintMessage(11, " ", enemy->Params.Frost);
    PrintMessage(8, " ", enemy->Params.Dark);
    PrintMessage(13, " ", enemy->Params.Psycho);
    PrintMessage(7, "\n");
  }
  for (int i = 1; i <= Game.GMBattle.StageBosses.size(); i++) {
    Creature* enemy = Game.GMBattle.StageBosses[i - 1];
    PrintMessage(7, i, ". ");
    if (enemy->Params.HP >= enemy->Params.HPMax / 2) {
      PrintMessage(15, enemy->Params.CalmText);
    } else {
      if (enemy->Params.HP >= enemy->Params.HPMax / 4) {
        PrintMessage(15, enemy->Params.HurtText);
      } else {
        PrintMessage(15, enemy->Params.DamagedText);
      }
    }
    PrintMessage(12, " ", enemy->Params.Flame);
    PrintMessage(11, " ", enemy->Params.Frost);
    PrintMessage(8, " ", enemy->Params.Dark);
    PrintMessage(13, " ", enemy->Params.Psycho);
    PrintMessage(7, "\n");
  }
  PrintMessage(11, "\nLast Mage\n");
  PrintMessage(15, "Health: ");
  PrintMessage(4, Game.Player.Params.HP);
  PrintMessage(15, " Mana: ");
  PrintMessage(3, Game.Player.Params.Mana, "\n");
  PrintMessage(10, Game.Player.Params.Poison, " ");
  PrintMessage(9, Game.Player.Params.Disease, " ");
  PrintMessage(8, Game.Player.Params.Mechanization, " ");
  PrintMessage(12, Game.Player.Params.Stealer, "\n");
  battleActions = Game.BattleGetActions();
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
  choice = TakeInt(1, battleActions.size());
  switch (battleActions[choice - 1]) {
    case BattleActions::Regenerate:
      Game.BattleAct(BattleActions::Regenerate);
      PrintMessage(15, "Last Mage started regenerating\n");
      break;

    case BattleActions::SupportSpell:
      PrintMessage(15, "Choose spell:\n");
      PrintMessage(15, "1. Steel blood. Decrease incoming damage by half\n");
      PrintMessage(15, "2. Blue heart. Heal ");
      PrintMessage(4, "50\n");
      PrintMessage(15, "3. Radiance. Heal ");
      PrintMessage(4, "80");
      PrintMessage(15, " but incoming damage rise by half\n");
      Game.BattleAct(BattleActions::SupportSpell, TakeInt(1, 4));
      break;

    case BattleActions::Spell:
      PrintMessage(15,
                   "Choose element:\n1. Flame. Burn enemy "
                   "slowly\n2. Frost. Make enemy "
                   "attacks weaker\n3. Dark. With darken mind "
                   "enemy may miss\n4. Psycho. "
                   "Enemy may lose control and attack self\n");
      spell = TakeInt(1, 4);
      PrintMessage(15, "Select enemy\n");
      Game.BattleAct(BattleActions::Spell, spell, SelectTarget());
      break;

    case BattleActions::PowerfulSpell:
      PrintMessage(15, "Select enemy\n");
      Creature* target = SelectTarget();
      PrintMessage(
          15,
          "Choose catalyst\n1. Flame. Ignite element. Doesn't damage but "
          "increase status much\n2. Frost. Break element. Increase "
          "damage and "
          "status\n3. Dark. Nullify element. Doesn't create status but "
          "make damage bigger\n4. Psycho. Overload element. Deal low "
          "heal to enemy but add large status\n");
      spell = TakeInt(1, 4);
      PrintMessage(15,
                   "Choose element:\n1. Flame. Burn enemy "
                   "slowly\n2. Frost. Make enemy "
                   "attacks weaker\n3. Dark. With darken mind "
                   "enemy may miss\n4. Psycho. "
                   "Enemy may lose control and attack self\n");
      Game.BattleAct(BattleActions::PowerfulSpell, spell, target,
                     TakeInt(1, 4));
      break;
  }
}

void ConsoleUI::Run() {
  while (Game.Player.Alive) {
    switch (Game.State) {
      case GMStates::Battle:
        Battle();
        break;
      case GMStates::Inventory:
        break;
      case GMStates::Map:
        break;
    }
  }
}

void ConsoleUI::CallAct(RenderActions const action, int ID, int params) {
  Creature* target;
  if (ID == -1) {
    target = &Game.Player;
  } else {
    if (ID >= 10000) {
      target = Game.GMBattle.StageBosses[ID - 10000];
    } else {
      target = Game.GMBattle.Enemies[ID];
    }
  }
  switch (action) {
    case RenderActions::Attack:
      PrintMessage(
          15, target->Params.AtkTexts[rand() % target->Params.AtkTexts.size()],
          "\n");
      break;

    case RenderActions::SupportSpell:
      switch (params) {
        case 1:
          CleanRender();
          PrintMessage(15, "Last mage blood became gray. His protction rise\n");
          break;
        case 2:
          CleanRender();
          PrintMessage(15,
                       "Last Mage heart beat strong and slow, "
                       "regenerating his health\n");
          break;
        case 3:
          CleanRender();
          PrintMessage(
              15,
              "Last Mage heart glow inside his chest, refilling his health. He "
              "is vulnerable now\n");
          break;
      }
      break;

    case RenderActions::TakeDamage:
      PrintMessage(15, target->Params.Name, " recieved ", params, " damage\n");
      break;

    case RenderActions::SpecialAttack:
      switch (target->Params.SpecAtkID) {
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
          PrintMessage(15, "Witch created cluster of arms\n");
          PrintMessage(
              15,
              "Witch tried to create more arms but overloaded herself - 20 "
              "damage\n");
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
              15, "Tyrant emits a mighty roar and strike with all limbs. ");
          break;
        case 7:
          PrintMessage(
              15,
              "Halo shine with purple light. Light heal all enemies by 20 "
              "health\n");
          break;
      }
      break;

    case RenderActions::Death:
      if (ID == -1) {
        PrintMessage(15, "Last Mage fell\n\n");
      } else {
        PrintMessage(15, target->Params.DeathText, "\n");
      }
      break;

    case RenderActions::AtkPreparing:
      switch (target->Params.SpecAtkID) {
        case 6:
          PrintMessage(15, "Tyrant prepares something, her core glow bright\n");
          break;
      }
      break;

    case RenderActions::Appear:
      switch (target->Params.SpecAtkID) {
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
          PrintMessage(4, "InfArmY");
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
          PrintMessage(12, "- Powerful treat detected. Starting battle\n ");
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

int ConsoleUI::TakeInt(int const min, int const max) {
  int Chosen;
  do {
    while (!(std::cin >> Chosen)) {
      PrintMessage(4, "Invalid choice\n");
      std::cin.clear();
      std::cin.ignore();
    }
    if ((Chosen < min) or (Chosen > max)) {
      PrintMessage(4, "Invalid choice!\n");
      std::cin.clear();
      std::cin.ignore();
    } else {
      return Chosen;
    }
  } while (true);
}

Creature* ConsoleUI::SelectTarget() {
  int size = Game.GMBattle.Enemies.size() + Game.GMBattle.StageBosses.size();
  int choice = TakeInt(1, size) - 1;
  if (choice < Game.GMBattle.Enemies.size()) {
    return Game.GMBattle.Enemies[choice];
  } else {
    return Game.GMBattle.StageBosses[choice - Game.GMBattle.Enemies.size()];
  }
}