#pragma once

using namespace std;

// 아이템 효과 타입
enum class ItemEffectType
{
	None,
	Heal,		// 체력회복
	AttackUp	// 공격력 증가
};

class Item
{
private:
	string sItemName;	// 아이템 이름
	int price;			// 아이템 가격
	int itemCount;		// 수량
	ItemEffectType effectType;	// 아이템 효과 타입
	int effectValue;	// 효과 수치		

public:
	Item(string itemName_, int price_, int itemCount_, ItemEffectType type_, int value_);	// 생성자

	// Getter
	const string& GetsItemName() const;
	int GetiPrice() const;
	int GetiItemCount() const;
	ItemEffectType GetEffectType() const;
	int GetEffectValue() const;

	// Setter
	void SetsItemName(const string& sItemName_);
	void SetiPrice(const int& price_);
	void SetsItemCount(const int& ItemCount_);

	void AddItemCount(int amount);	// 아이템 수량 증가
	void ReduceItemCount(int amount);	// 아이템 수량 증가
};

