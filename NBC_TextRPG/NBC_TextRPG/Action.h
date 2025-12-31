#pragma once

class Character;
class Item;
struct ActionContext
{
	Character* owner = nullptr;
	Character* target = nullptr;
	Item* useItem = nullptr;
};

class Action
{
public:
	virtual ~Action() = 0;
	virtual void Play(const ActionContext& context) = 0;

};
