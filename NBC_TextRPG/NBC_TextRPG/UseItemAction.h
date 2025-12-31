#pragma once
#include "Action.h"

class UseItemAction : public Action
{
public:
	void Play(const ActionContext& context) override;
};
