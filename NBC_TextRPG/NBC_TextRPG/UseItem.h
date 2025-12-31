#pragma once
#include "Action.h"

class UseItem : public Action
{
public:
	void Play(const ActionContext& context) override;
};
