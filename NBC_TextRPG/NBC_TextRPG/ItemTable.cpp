#include "pch.h"
#include "ItemTable.h"
#include "Item.h"

ItemTable::ItemTable()
{
	Init(); 
}

void ItemTable::Init()
{
	// 아이템 "붕대" 추가
	Item Bandage;
	Bandage.GetItemInfo().name = "붕대";
	Bandage.GetItemInfo().price = 50;
	Bandage.GetItemInfo().effectType = ItemEffectType::Heal;
	Bandage.GetItemInfo().effectValue = 50;
	Bandage.GetItemInfo().itmeUseMessage = "붕대로 상처부위를 치료했습니다.";
	table["붕대"] = Bandage;

	// 아이템 "아드레날린" 추가
	Item Adrenaline;
	Adrenaline.GetItemInfo().name = "아드레날린";
	Adrenaline.GetItemInfo().price = 150;
	Adrenaline.GetItemInfo().effectType = ItemEffectType::AttackUp;
	Adrenaline.GetItemInfo().effectValue = 10;
	Bandage.GetItemInfo().itmeUseMessage = "힘이 넘치는것 같다";
	table["아드레날린"] = Adrenaline;

}

Item ItemTable::GetItem(const string& itemName) const
{
	auto it = table.find(itemName);
	if (it != table.end())
		return it->second;

	return Item();
}
