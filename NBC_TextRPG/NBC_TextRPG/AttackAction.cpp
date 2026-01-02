#include "pch.h"
#include "AttackAction.h"


AttackAction::~AttackAction()
{}

void AttackAction::Play(const ActionContext& context)
{
	CanPlay(context);

	context.target->TakeDamage(50); 
}

bool AttackAction::CanPlay(const ActionContext& context)
{
	// 공격자, 공격대상 존재 확인
	if (!context.owner || !context.target)
		return false;

	// 공격자 생존 확인
	if (context.owner->stats.bIsDead == true)
		return false;


	return true; 

}
