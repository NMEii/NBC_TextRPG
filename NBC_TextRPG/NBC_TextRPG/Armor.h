#pragma once
#include "Weapon.h"

class Armor : public Weapon {
public:
	void OnTakeDamage(Character* owner, Character* attacker, int damage) override;
};