#ifndef CONTROLPACKAGE_HPP
#define CONTROLPACKAGE_HPP
#include "Button.h"

struct ControlPackage
{
public:
  int vcursor;
  int deltaTime;
  Button* btnSubmit;
  Button* btnCancel;
};

#endif

