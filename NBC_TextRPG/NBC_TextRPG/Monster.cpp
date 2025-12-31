#include "Monster.h"
#include<iostream>

//입력 받을때
Monster::Monster(std::string name, int playerLevel) :Character(name)
{
	level = playerLevel;
	health = playerLevel * 50;
	maxHealth = playerLevel * 50;
	attack = playerLevel * 15;
}


