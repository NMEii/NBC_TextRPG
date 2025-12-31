#include "pch.h"
#include "Attack.h"



//Attack, Action 초기화
Attack::Attack(Character* owner) : Action(owner)
{}

void Attack::Play(Character* target)
{
	//공격자 사망 확인
	if (owner->stats.bIsDead == true)
		return;

	//피격자 체력 감소
	target->stats.currentHealth -= owner->stats.attack;

	//피격자 사망 판정
	if (target->stats.currentHealth <= 0)
	{
		target->stats.currentHealth = 0;
		target->stats.bIsDead = true;
	}
}