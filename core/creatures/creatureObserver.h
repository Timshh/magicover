#pragma once
#include <vector>

#include "uiController.h"
#include "uiData.h"

class CreatureObserver {
 public:
  void AddSubscriber(UIController* const subscriber);
  void RemoveSubscriber(UIController* const subscriber);
  CreatureObserver();

 private:
  std::vector<UIController*> Subscribers;
};