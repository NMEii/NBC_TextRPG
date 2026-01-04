#include "pch.h"
#include "UseItemAction.h"
#include "Item.h"
#include "Player.h"
#include "Inventory.h"


void UseItemAction::Play(const ActionContext& context)
{
	// 사용자 사용, 사용 아이템 존재 확인
	if (!context.ownerPlayer || !context.useItem)
		return;

	////사용할 아이템 갯수 확인
	//if (context.useItem->GetiItemCount() <= 0)
	//	return;

	const ItemInfo& itemInfo = context.useItem->GetItemInfo();

	switch (itemInfo.effectType)
	{
	case ItemEffectType::Heal:

		//currentHP 증가
		context.ownerPlayer->stats.currentHealth += itemInfo.effectValue;

		//HP 초과 회복시 max값으로 재조정
		if (context.ownerPlayer->stats.currentHealth > context.ownerPlayer->stats.maxHealth)
		{
			context.ownerPlayer->stats.currentHealth = context.ownerPlayer->stats.maxHealth;
		}

		break;
	case ItemEffectType::AttackUp:
		//attack 증가
		context.ownerPlayer->stats.attack += itemInfo.effectValue;
		
		break;

	default:
		break;
	}

	//아이템 사용시 갯수 -1
	context.ownerPlayer->GetInventory()->RemoveItem(itemInfo.name, 1);
}
