#include "pch.h"
#include "Attack.h"


void Attack::Play(const ActionContext& context)
{
	// 공격자, 공격대상 존재 확인
	if (!context.owner || !context.target)
		return;

	// 공격자 생존 확인
	if (context.owner->stats.bIsDead == true)
		return;

	//공격 대상 체력 감소
	context.target->stats.currentHealth -= context.owner->stats.attack;

	//공격 대상 사망 판정
	if (context.target->stats.currentHealth <= 0)
	{
		context.target->stats.currentHealth = 0;
		context.target->stats.bIsDead = true;
	}
}