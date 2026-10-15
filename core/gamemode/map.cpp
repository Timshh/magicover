#include "map.h"

Map::Map() { CreateMap(); }

void Map::CreateMap() {
  current_map_ = generator_.GenerateMap();
  current_location_ = 0;
}

int Map::MapAct(const int way) {
  current_location_ = way;
  return current_map_.nodes[current_location_].type;
}

int Map::GetNodeType(const int id) { return current_map_.nodes.at(id).type; }

std::vector<int> Map::GetWays() {
  return current_map_.nodes[current_location_].next;
}
