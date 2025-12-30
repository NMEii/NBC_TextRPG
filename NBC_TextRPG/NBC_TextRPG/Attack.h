#pragma once
#include "Action.h"
#include "Character.h"

class Attack :
    public Action
{
  void Play(Character* onwer, Character* target);
};

