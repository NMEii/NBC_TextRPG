#pragma once
#include"Monster.h"
#include"pch.h"



class Generate_monster
{
public:
	static Monster* generate(int playerLevel);

private:
	static std::vector<std::string> monsterName;
};

