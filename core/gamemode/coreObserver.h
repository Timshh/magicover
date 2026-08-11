#pragma once
#include <vector>

#include "uiData.h"
#include "uiController.h"

class CoreObserver {
 public:
  void AddSubscriber(UIController* const subscriber);
  void RemoveSubscriber(UIController* const subscriber);
  void CallAct(RenderActions const action, int ID, int params = 0);
  CoreObserver();

 private:
  std::vector<UIController*> Subscribers;
};