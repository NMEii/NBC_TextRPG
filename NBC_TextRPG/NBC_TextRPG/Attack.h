#pragma once
#include "Action.h"
#include "Character.h"

class Attack : public Action
{
public:
	void Play(const ActionContext& context) override;
};

