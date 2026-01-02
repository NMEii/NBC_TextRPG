#include "pch.h"
#include "Item.h"

Item::Item(ItemInfo InInfo) : info(InInfo)
{
	itemCount = 0;
}

const ItemInfo Item::GetItemInfo() const
{
	return info;
}

int Item::GetiItemCount() const
{
	return itemCount;
}

void Item::SetItemInfo(const ItemInfo& InInfo)
{
	info = InInfo;
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

