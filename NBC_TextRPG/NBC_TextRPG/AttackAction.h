#pragma once
#include "Action.h"
#include "Character.h"

class AttackAction : public Action
{
public:
	~AttackAction();
	void Play(const ActionContext& context) override;

	bool CanPlay(const ActionContext& context);
};

