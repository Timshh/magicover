#include "map.h"

Map::Map(Renderer* render) {
  Render = render;
  CreateMap();
}

void Map::CreateMap() {
  CurrentMap = Generator.GenerateMap();
  CurrentLocation = CurrentMap.Start;
}

int Map::MapAct() {
  int Deed = 2, Choice;
  Render->PrintMessage(11, "\nLast Mage\n");
  Render->PrintMessage(15, "1. Rings\n");
  for (int i = 0; i < CurrentMap.Nodes[CurrentLocation].Next.size(); i++) {
    Render->PrintMessage(15, Deed, ". ");
    switch (CurrentMap.Nodes[CurrentMap.Nodes[CurrentLocation].Next[i]].Type) { 
        case 1:
            Render->PrintMessage(15, "Boss");
            break;
        case 2:
          Render->PrintMessage(15, "Enemy");
          break;
        case 3:
          Render->PrintMessage(15, "Powerful enemy");
          break;
        case 4:
          Render->PrintMessage(15, "Mana room");
          break;
        case 5:
          Render->PrintMessage(15, "Unknown Room");
          break;
    }
    Render->PrintMessage(15, "\n");
    
    Deed++;
  }
  std::cin >> Choice;
  if (Choice < Deed and Choice > 0) {
    Deed = 0;
    switch (Choice) {
      case 1:
        Render->CleanRender();
        return 0;
        break;
      default:
        CurrentLocation = CurrentMap.Nodes[CurrentLocation].Next[Choice-2];
    }
    if (CurrentLocation != CurrentMap.Boss) {
      return CurrentMap.Nodes[CurrentLocation].Type;
    }
    
  } else {
    Render->CleanRender();
    Render->PrintMessage(4, "That didn't work\n");
    return -1;
  }
}

