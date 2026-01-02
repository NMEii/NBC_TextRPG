#include "Monster.h"
#include "Attack.h"
#include"pch.h"

//입력 받을때
Monster::Monster(std::string name, int playerLevel) :Character(name)
{
	stats.currentHealth = playerLevel * 50;
	stats.maxHealth = playerLevel * 50;
	stats.attack = playerLevel * 15;

	


	AddActions(std::make_unique<AttackAction>());
}

void Monster::AttackTarget(Character* target)
{
	ActionContext ctx;
	ctx.target = target;

	PlayAction(0, ctx);
}

