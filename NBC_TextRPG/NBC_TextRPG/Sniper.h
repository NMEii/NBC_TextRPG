#pragma once
#include "Weapon.h"

class Sniper : public Weapon
{
public:
	void OnPreAttack(Character* owner, int& outDamage) override;
};