#include "mapgenerator.h"

MapGenerator::MapGenerator() {}

MapGraph MapGenerator::GenerateMap(int layers, int minNodes, int maxNodes) {
  MapGraph Graph;

  std::vector<std::vector<int>> LayersNodes;

  LayersNodes.resize(layers);

  for (int layer = 0; layer < layers; ++layer) {
    int nodesInLayer = rand() % (maxNodes - minNodes) + minNodes;
    for (int i = 0; i < nodesInLayer; ++i) {
      Node Node;
      Node.ID = Graph.Nodes.size();
      Node.Layer = layer;
      Node.Type = rand() % 4 + 2;

      Graph.Nodes.push_back(Node);
      LayersNodes[layer].push_back(Node.ID);
    }
  }

  Graph.Start = LayersNodes.front().front();
  Graph.Boss = LayersNodes.back().front();
  Graph.Nodes[Graph.Boss].Type = 1;

  for (int layer = 0; layer < layers - 1; ++layer) {
    for (int nodeId : LayersNodes[layer]) {
      std::vector<int>& NextLayer = LayersNodes[layer + 1];
      int connections = rand()%NextLayer.size()+1;
      for (int c = 0; c < connections; ++c) {
        int target = NextLayer[c];
        Graph.Nodes[nodeId].Next.push_back(target);
      }
    }
  }

  for (int layer = 1; layer < layers; ++layer) {
    for (int nodeId : LayersNodes[layer]) {
      bool hasIncoming = false;

      for (Node& n : Graph.Nodes) {
        for (int to : n.Next) {
          if (to == nodeId) {
            hasIncoming = true;
            break;
          }
        }
        if (hasIncoming) break;
      }

      if (!hasIncoming) {
        std::vector<int> prevLayer = LayersNodes[layer - 1];
        int prev = prevLayer[rand() % (prevLayer.size() - 1)];
        Graph.Nodes[prev].Next.push_back(nodeId);
      }
    }
  }
  int bossNode = Graph.Boss;

  std::vector<int>& lastLayer = LayersNodes[layers - 2];

  for (int nodeId : lastLayer) {
    Graph.Nodes[nodeId].Next.push_back(bossNode);
  }

  return Graph;
}