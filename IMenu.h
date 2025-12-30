#pragma once
#include <functional>
#include "UIRequest.h"



class IMenu
{
public:
    virtual ~IMenu() = default;

    virtual void Render() = 0;
    virtual void Update() = 0;
    virtual int HandleInput(int range) = 0;

    std::function<void(UIRequest)> OnRequest;
};

