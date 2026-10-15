#pragma once
#include <vector>

#include "ui_data.h"
#include "ui_controller.h"

class CoreObserver {
 public:
  void AddSubscriber(UIController* const subscriber);
  void RemoveSubscriber(UIController* const subscriber);
  void CallAct(const RenderActions action, const int id = -2,
               const int params = 0, const int subparams = 0);
  CoreObserver();

 private:
  std::vector<UIController*> subscribers_;
};