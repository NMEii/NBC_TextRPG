#include "pch.h"
#include "Sniper.h"
#include "Random.h"

using namespace Random;

void Sniper::OnPreAttack(Character* owner, int& outDamage)
{
	// 30% 확률로 크리티컬 (데미지 2배)
	if (Success(0.9))
	{
		outDamage *= 2;
		if (owner)
		{
			owner->AddMessage("[패시브: Sniper] 크리티컬 히트!\n");
		}
	}
}