#include "map.h"

Map::Map() { CreateMap(); }

void Map::CreateMap() {
  CurrentMap = Generator.GenerateMap();
  CurrentLocation = 0;
}

int Map::MapAct(int const way) {
  CurrentLocation = way;
  return CurrentMap.Nodes[CurrentLocation].Type;
}

int Map::GetNodeType(int const id) { return CurrentMap.Nodes.at(id).Type; }

std::vector<int> Map::GetWays() {
  return CurrentMap.Nodes[CurrentLocation].Next;
}
