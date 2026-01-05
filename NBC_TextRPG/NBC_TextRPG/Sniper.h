#pragma once
#include "Weapon.h"

class Sniper : public Weapon
{
public:
	void OnPreAttack(int& outDamage) override;
};