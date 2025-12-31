#pragma once
#include "Action.h"
#include "Character.h"

class Attack : public Action
{
public:
	Attack(Character* owner);
	void Play(Character* target) override;
};

