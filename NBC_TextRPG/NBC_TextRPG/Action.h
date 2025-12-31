#pragma once

class Character;
class Item;

//다양한 대상을 유동적으로 지정할 수 있는 ActionContext struct
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
