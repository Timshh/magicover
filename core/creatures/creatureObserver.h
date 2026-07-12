#pragma once
#include <vector>

#include "renderData.h"
#include "renderer.h"

class CreatureObserver {
 public:
  void AddSubscriber(Renderer* subscriber);
  void RemoveSubscriber(Renderer* subscriber);
  void CallAct(RenderActions action);
  CreatureObserver();

 private:
  std::vector<Renderer*> Subscribers;
};