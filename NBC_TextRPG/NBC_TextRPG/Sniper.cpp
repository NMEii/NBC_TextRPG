#include "pch.h"
#include "Sniper.h"
#include "Random.h"

using namespace Random;

void Sniper::OnPreAttack(int& outDamage)
{
	// 30% 확률로 크리티컬 (데미지 2배)
	if (Success(0.3)) {
		outDamage *= 2;
		std::cout << "[패시브: Sniper] 크리티컬 히트!\n";
	}
}