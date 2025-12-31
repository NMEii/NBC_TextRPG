#pragma once
#include"Character.h"

class Monster :public Character
{
public:
	Monster(std::string name, int level);

	void AttackTarget(Character* target);
};