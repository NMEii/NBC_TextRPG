#include "pch.h"
#include "Armor.h"
#include "Random.h"

using namespace Random;

void Armor::OnTakeDamage(Character* owner, Character* attacker, int damage)
{
	// 랜덤한 데미지 반사
	if (attacker)
	{
		int reflect = (damage * Choice(0, 100)) / 100;
		if (reflect > 0)
		{
			std::cout << "[패시브: Armor] " << reflect << " 데미지 반사!\n";
			attacker->TakeDamage(reflect);
		}
	}
}
