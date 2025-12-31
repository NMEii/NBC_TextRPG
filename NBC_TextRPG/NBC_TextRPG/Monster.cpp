#include "Monster.h"
#include "Attack.h"
#include<memory>
#include<iostream>

//입력 받을때
Monster::Monster(std::string name, int playerLevel) :Character(name)
{
	level = playerLevel;
	health = playerLevel * 50;
	maxHealth = playerLevel * 50;
	attack = playerLevel * 15;
	
	AddActions(std::make_unique<Attack>());
}

void Monster::AttackTarget(Character* target)
{
	ActionContext ctx;
	ctx.target = target;

	PlayAction(0, ctx);
}

