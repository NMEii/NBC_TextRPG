#pragma once

using namespace std;

// 아이템 효과 타입
enum class ItemEffectType
{
	None,
	Heal,		// 체력회복
	AttackUp	// 공격력 증가
};

struct ItemInfo
{
	string name = "";	// 아이템 이름
	int price = 0;			// 아이템 가격
	ItemEffectType effectType = ItemEffectType::None;	// 아이템 효과 타입
	int effectValue = 0;	// 효과 수치		

};

class Item
{
private:
	
	ItemInfo info;
	int itemCount;		// 수량

public:
	Item(ItemInfo InInfo);	// 생성자

	// Getter
	const ItemInfo GetItemInfo() const;
	int GetiItemCount() const;

	// Setter
	void SetItemInfo(const ItemInfo& InInfo);
	void SetsItemCount(const int& ItemCount_);

	void AddItemCount(int amount);	// 아이템 수량 증가
	void ReduceItemCount(int amount);	// 아이템 수량 증가
};

