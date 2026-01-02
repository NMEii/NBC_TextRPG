#include "pch.h"
#include "ItemTable.h"
#include "Item.h"

void ItemTable::Init()
{
	// 아이템 "붕대" 추가
	Item* Bandage = new Item();
	Bandage->GetItemInfo().name = "붕대";
	Bandage->GetItemInfo().price = 50;
	Bandage->GetItemInfo().effectType = ItemEffectType::Heal;
	Bandage->GetItemInfo().effectValue = 50;
	table["붕대"] = Bandage;
	delete Bandage;

	// 아이템 "아드레날린" 추가
	Item* Adrenaline = new Item();
	Adrenaline->GetItemInfo().name = "아드레날린";
	Adrenaline->GetItemInfo().price = 150;
	Adrenaline->GetItemInfo().effectType = ItemEffectType::AttackUp;
	Adrenaline->GetItemInfo().effectValue = 10;
	table["아드레날린"] = Adrenaline;
	delete Adrenaline;
}

Item* ItemTable::GetItem(string itemName) const
{
	for (const auto& pair : table)
	{
		if (pair.first == itemName)
		{
			return pair.second;
		}
	}
	return nullptr;
}

