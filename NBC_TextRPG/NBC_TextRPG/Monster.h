#pragma once
#include"Character.h"

class Monster :public Character
{
public:
	Monster();
	Monster(std::string name, int level, int artIndex);
	~Monster();

	string GetMonsterName() { return stats.name; }

	void AttackTarget(Character* target);
	int getArtindex();
	vector<std::string> GetImageVector() const;

private:
	int artIndex;

	static const std::vector<vector<std::string>> MonsterImages;
};