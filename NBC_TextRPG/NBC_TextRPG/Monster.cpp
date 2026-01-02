#include"pch.h"
#include "Monster.h"
#include "AttackAction.h"
#include"Random.h"

//입력 받을때
Monster::Monster(std::string name, int playerLevel) :Character(name)
{
	stats.currentHealth = playerLevel * Random::Choice(20, 30);
	stats.maxHealth = playerLevel * Random::Choice(20, 30);
	stats.attack = playerLevel * Random::Choice(5, 10);

	AddActions(std::make_unique<AttackAction>());
}

void Monster::AttackTarget(Character* target)
{
	ActionContext ctx;
	ctx.target = target;

	PlayAction(0, ctx);
}

