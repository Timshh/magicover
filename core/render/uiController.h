#pragma once
#include <iostream>

#include "uiData.h"

class UIController {
 public:
  UIController();
  void virtual CallAct(RenderActions const action, int ID, int params, int subparams);
};