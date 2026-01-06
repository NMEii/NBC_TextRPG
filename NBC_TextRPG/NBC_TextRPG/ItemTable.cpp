#include "pch.h"
#include "ItemTable.h"
#include "Item.h"
#include "Random.h"

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
	table["붕대"] = Bandage;

	// 아이템 "아드레날린" 추가
	Item Adrenaline;
	Adrenaline.GetItemInfo().name = "아드레날린";
	Adrenaline.GetItemInfo().price = 150;
	Adrenaline.GetItemInfo().effectType = ItemEffectType::AttackUp;
	Adrenaline.GetItemInfo().effectValue = 10;
	table["아드레날린"] = Adrenaline;

}

Item* ItemTable::GetItem(const string& itemName) 
{
	auto it = table.find(itemName);
	if (it != table.end())
		return &it->second;

	return nullptr;
}
	

Item* ItemTable::GetRandomItem()
{
	int randNum = Random::Choice(0, table.size() - 1);
	
	auto it = table.begin();

	for (int i = 0; i < randNum; i++)
		it++;

	return &it->second; 
}
