#pragma once
#include "Weapon.h"

class DualGun : public Weapon
{
public:
	void OnPostAttack(Character* owner, Character* target) override;
};