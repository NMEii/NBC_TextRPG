#pragma once

using namespace std;

// 아이템 효과 타입
enum class ItemEffectType
{
	None,
	Heal,		// 체력회복
	AttackUp,	// 공격력 증가
	Stimulate,
	LevelUp,
	Ending
};

struct ItemInfo
{
	string name = "";	// 아이템 이름
	int price = 0;			// 아이템 가격
	ItemEffectType effectType = ItemEffectType::None;	// 아이템 효과 타입
	int effectValue = 0;	// 효과 수치		
	string itmeUseMessage;
};

class Item
{
private:
	
	ItemInfo info;
	int itemCount;		// 수량

public:
	Item();	// 생성자

	// Getter
	ItemInfo& GetItemInfo();
	int GetiItemCount() const;

	// Setter
	void SetItemInfo(const ItemInfo& InInfo);
	void SetsItemCount(const int& ItemCount_);

	void IncreaseCount(int amount);	// 아이템 수량 증가
	void ReduceItemCount(int amount);	// 아이템 수량 증가
};
