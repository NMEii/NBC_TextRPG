#include "pch.h"
#include "BossMonster.h"
#include "AttackAction.h"
#include "Random.h"

BossMonster::BossMonster()
{
	artIndex = 3; 

	stats.maxHealth = 10 * Random::Choice(30, 45)*artIndex;
	stats.currentHealth = stats.maxHealth;

	stats.attack = 10 * Random::Choice(7, 15);

	stats.name = "Boss Monster";
	AddActions(std::make_unique<AttackAction>());
}
