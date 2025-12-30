#pragma once
#include "IMenu.h"

class BaseUI :IMenu
{
public:
    virtual void Render() override; 

    virtual void Update() override; 

    virtual int HandleInput(int range) override; 

};

