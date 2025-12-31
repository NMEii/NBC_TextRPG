#pragma once
#include "Action.h"

class UseItem : public Action
{
public:
	UseItem(Character* owner);
	void Play(Character* target) override;
};
