#include "pch.h"
#include "Item.h"

Item::Item(string itemName_, int price_, int itemCount_, ItemEffectType type_, int value_) :
	sItemName(itemName_),
	price(price_),
	itemCount(itemCount_),
	effectType(type_),
	effectValue(value_)
{
}

const string& Item::GetsItemName() const
{
	return sItemName;
}

int Item::GetiPrice() const
{
	return price;
}

int Item::GetiItemCount() const
{
	return itemCount;
}

ItemEffectType Item::GetEffectType() const
{
	return effectType;
}

int Item::GetEffectValue() const
{
	return effectValue;
}

void Item::SetsItemName(const string& sItemName_)
{
	sItemName = sItemName_;
}

void Item::SetiPrice(const int& price_)
{
	price = price_;
}

void Item::SetsItemCount(const int& iItemCount_)
{
	itemCount = iItemCount_;
}

void Item::AddItemCount(int amount)
{
	itemCount += amount;
}

void Item::ReduceItemCount(int amount)
{
	itemCount -= amount;
}

const string& Item::GetsItemName() const
{
	// TODO: 여기에 return 문을 삽입합니다.
}
