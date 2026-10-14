#pragma once
#include <vector>

#include "ui_controller.h"
#include "ui_data.h"

class CreatureObserver {
 public:
  void AddSubscriber(UIController* const subscriber);
  void RemoveSubscriber(UIController* const subscriber);
  CreatureObserver();

 private:
  std::vector<UIController*> Subscribers;
};