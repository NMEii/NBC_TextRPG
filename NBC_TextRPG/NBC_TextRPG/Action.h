#pragma once

class Character;

class Action
{
public:
	Action(Character* owner);
	virtual ~Action() = 0;
	virtual void Play(Character* target) = 0;
protected:
	Character* owner;
};
