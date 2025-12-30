#include "Monster.h"
#include<iostream>


Monster::Monster(std::string name, int playerLevel):Character(name)
{
	level = playerLevel;
	health = playerLevel * 50;
	maxHealth = playerLevel * 50;
	attack = playerLevel * 15;
}
void Monster::takeDamage(int dmg)
{
	health -= dmg;
	if (health < 0) health = 0;
	std::cout << "괴물이 " << dmg << "의 피해를 입었다!\n";
}

