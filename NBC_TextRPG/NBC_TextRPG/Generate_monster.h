#pragma once
#include"pch.h"
#include"Monster.h"


class Generate_monster
{
public:
	static Monster* generate(int playerLevel);

private:
	static std::vector<std::string> monsterName;
};

