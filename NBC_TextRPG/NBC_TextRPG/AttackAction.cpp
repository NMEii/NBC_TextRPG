#include "pch.h"
#include "AttackAction.h"


AttackAction::~AttackAction()
{
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

void AttackAction::Play(const ActionContext& context)
{
	if (!CanPlay(context))
		return;

	int finalDamage = context.owner->stats.attack;
	Weapon* weapon = nullptr;

	if (context.ownerPlayer) {
		weapon = context.ownerPlayer->GetWeapon();
	}

	if (weapon) {
		weapon->OnPreAttack(finalDamage); // Sniper라면 여기서 데미지 2배
	}

	context.target->TakeDamage(finalDamage);

	if (weapon) {
		weapon->OnPostAttack(context.owner, context.target);
	}
}

