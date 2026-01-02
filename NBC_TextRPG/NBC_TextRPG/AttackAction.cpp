#include "pch.h"
#include "AttackAction.h"


AttackAction::~AttackAction()
{}

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

void AttackAction::Play(const ActionContext& context)
{
	if (!CanPlay(context))
		return;

	context.target->TakeDamage(context.owner->stats.attack); 
}

