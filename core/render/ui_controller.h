#pragma once
#include <iostream>

#include "ui_data.h"

class UIController {
 public:
  UIController();
  void virtual CallAct(const RenderActions action, const int id,
                       const int params, const int subparams);
};