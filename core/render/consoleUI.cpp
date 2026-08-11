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
      PrintMessage(15, target->Params.Name, " attacks\n");
      break;
    case RenderActions::TakeDamage:
      PrintMessage(15, target->Params.Name, " recieved ", params, " damage\n");
      break;
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