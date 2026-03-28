#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

struct Node {
  int ID, Layer, Type;
  std::vector<int> Next;
};

struct MapGraph {
  std::vector<Node> Nodes;
  int Start, Boss;
};



class MapGenerator{
 public:
  MapGenerator();
  MapGraph GenerateMap(int layers = 10, int minnodes = 2, int maxnodes = 5);
};