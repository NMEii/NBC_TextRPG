#include "pch.h"
#include "Armor.h"
#include "Random.h"

using namespace Random;
using namespace std;

void Armor::OnTakeDamage(Character* owner, Character* attacker, int damage)
{
	if (attacker && owner)
	{
		int reflect = (damage * Choice(0, 100)) / 100;
		if (reflect > 0)
		{
			owner->AddMessage("[패시브: Armor] " + to_string(reflect) + " 데미지 반사!");
			attacker->TakeDamage(reflect);
		}
	}
}
