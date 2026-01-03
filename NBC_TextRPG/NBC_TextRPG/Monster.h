#pragma once
#include"Character.h"

class Monster :public Character
{
public:
	Monster();
	Monster(std::string name, int level, int _artIndex);
	~Monster();

	void AttackTarget(Character* target);

	string GetMonsterName();

	string GetImageString() const;

private:
	int artIndex;

	static const std::vector<std::string> MonsterImages;
};