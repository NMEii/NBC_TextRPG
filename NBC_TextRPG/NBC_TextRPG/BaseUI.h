#pragma once
#include "IMenu.h"

class BaseUI :IMenu
{
public:
    virtual void Render();

    virtual void Update();

    virtual int HandleInput(int range);

};

