#pragma once
#include <iostream>

#include "ui_data.h"

class UIController {
 public:
  UIController();
  void virtual CallAct(RenderActions const action, int ID, int params, int subparams);
};