#include "pch.h"
#include "UseItemAction.h"
#include "Item.h"
#include "Character.h"

void UseItemAction::Play(const ActionContext& context)
{
	// 사용자 사용, 사용 아이템 존재 확인
	if (!context.owner || !context.useItem)
		return;

	//사용할 아이템 갯수 확인
	if (context.useItem->GetiItemCount() <= 0)
		return;

	switch (context.useItem->GetEffectType())
	{
	case ItemEffectType::Heal:

		//currentHP 증가
		context.owner->stats.currentHealth += context.useItem->GetEffectValue();

		//HP 초과 회복시 max값으로 재조정
		if (context.owner->stats.currentHealth > context.owner->stats.maxHealth)
		{
			context.owner->stats.currentHealth = context.owner->stats.maxHealth;
		}

	case ItemEffectType::AttackUp:
		//attack 증가
		context.owner->stats.attack += context.useItem->GetEffectValue();
	}

	//아이템 사용시 갯수 -1
	context.useItem->SetsItemCount(context.useItem->GetiItemCount() - 1);
}
