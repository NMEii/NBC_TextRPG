#include "pch.h"
#include "DualGun.h"
#include "Random.h"

using namespace Random;

void DualGun::OnPostAttack(Character* owner, Character* target)
{
	if (Success(0.9))
	{
		if (owner)
		{
			owner->AddMessage("[패시브: DualGun] 연속 사격 발동!\n");
			target->TakeDamage(owner->stats.attack);
		}
	}
}
