#pragma once
#include"Character.h"

class Monster :public Character
{
public:
	Monster();
	Monster(std::string name, int level);
	~Monster();

	string GetMonsterName();
	void AttackTarget(Character* target);
};