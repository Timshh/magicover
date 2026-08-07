#include "map.h"

Map::Map() { CreateMap(); }

void Map::CreateMap() {
  CurrentMap = Generator.GenerateMap();
  CurrentLocation = CurrentMap.Start;
}

int Map::MapAct(int const way) {
  CurrentLocation = CurrentMap.Nodes[CurrentLocation].Next[way - 2];
  if (CurrentLocation != CurrentMap.Boss) {
    return CurrentMap.Nodes[CurrentLocation].Type;
  } else {
    return 0;
  }
}
