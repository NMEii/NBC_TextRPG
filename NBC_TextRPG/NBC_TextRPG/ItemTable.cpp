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
	Bandage.GetItemInfo().itmeUseMessage = "붕대로 상처부위를 치료했습니다.";
	Bandage.GetItemInfo().itemScript = "체력을 50만큼 회복합니다.";
	table["붕대"] = Bandage;

	// 아이템 "좋은회복약" 추가
	Item AIDKit;
	AIDKit.GetItemInfo().name = "좋은회복약";
	AIDKit.GetItemInfo().price = 100;
	AIDKit.GetItemInfo().effectType = ItemEffectType::Heal;
	AIDKit.GetItemInfo().effectValue = 100;
	AIDKit.GetItemInfo().itmeUseMessage = "좋은 회복약을 상처에 발랐다";
	AIDKit.GetItemInfo().itemScript = "체력을 100만큼 회복합니다.";
	table["좋은회복약"] = AIDKit;
	
	// 아이템 "아드레날린" 추가
	Item Adrenaline;
	Adrenaline.GetItemInfo().name = "아드레날린";
	Adrenaline.GetItemInfo().price = 150;
	Adrenaline.GetItemInfo().effectType = ItemEffectType::AttackUp;
	Adrenaline.GetItemInfo().effectValue = 10;
	Adrenaline.GetItemInfo().itmeUseMessage = "힘이 넘치는것 같다";
	Adrenaline.GetItemInfo().itemScript = "공격력이 10만큼 상승합니다.";
	table["아드레날린"] = Adrenaline;

	// 아이템 "스팀팩" 추가
	Item StimPack;
	StimPack.GetItemInfo().name = "스팀팩";
	StimPack.GetItemInfo().price = 100;
	StimPack.GetItemInfo().effectType = ItemEffectType::Stimulate;
	StimPack.GetItemInfo().effectValue = 20;
	StimPack.GetItemInfo().itmeUseMessage = "힘이 넘치는것 같다";
	StimPack.GetItemInfo().itemScript = "공격력이 20만큼 상승합니다."; 
	table["스팀팩"] = StimPack;

	// 아이템 "이상한사탕" 추가
	Item WeirdCandy;
	WeirdCandy.GetItemInfo().name = "이상한사탕";
	WeirdCandy.GetItemInfo().price = 500;
	WeirdCandy.GetItemInfo().effectType = ItemEffectType::LevelUp;
	WeirdCandy.GetItemInfo().effectValue = 1;
	WeirdCandy.GetItemInfo().itmeUseMessage = "레벨이 올랐다!";
	WeirdCandy.GetItemInfo().itemScript = "이상한 냄새가 나는 사탕이다.";
	table["이상한사탕"] = WeirdCandy;

	// 아이템 "환각치료제" 추가
	Item Medicine;
	Medicine.GetItemInfo().name = "환각치료제";
	Medicine.GetItemInfo().price = 500;
	Medicine.GetItemInfo().effectType = ItemEffectType::Ending;
	Medicine.GetItemInfo().effectValue = 1;
	Medicine.GetItemInfo().itmeUseMessage = "오....? 병권이의 상태가 이상하다!";
	Medicine.GetItemInfo().itemScript = "나는 분명 정신이 멀쩡한데 필요 없을거같다..";
	table["환각치료제"] = Medicine;

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
