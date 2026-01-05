#pragma once
#include "Character.h"

enum class WeaponType
{
	Sniper,	// 높은 공격력, 낮은 체력, 전용 패시브 : 크리티컬
	DualGun,// 균형 스텟, 전용 패시브 : 연속 사격 (확률로 한 번 더 공격)
	Armor	// 높은 체력, 낮은 공격력, 전용 패시브 : 반사 (랜덤한 데미지 반사)
};

class Weapon {
public:
	virtual ~Weapon() = default;

	virtual void OnPreAttack(int& outDamage) {}

	virtual void OnPostAttack(Character* owner, Character* target) {}

	virtual void OnTakeDamage(Character* owner, Character* attacker, int damage) {}
};