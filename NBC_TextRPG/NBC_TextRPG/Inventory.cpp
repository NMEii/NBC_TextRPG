#include "pch.h"
#include "Inventory.h"
#include "ItemTable.h"

Inventory::Inventory() : capacity(6)
{
	items.reserve(capacity);	// 인벤토리 최대용량 초기화
}

Inventory::~Inventory()
{
}

vector<shared_ptr<Item>> Inventory::GetInventory() const
{
	return items;
}

vector<string> Inventory::GetItemList()
{
	vector<string> nameList;
	int i = 0; 
	for (const auto& data : items)
	{
		nameList[i] = data->GetItemInfo().name;
		i++;
	}
	
	return nameList;
}

void Inventory::AddItem(Item* Item_, const int& itemCount_)
{
	string itemName_ = Item_->GetItemInfo().name;

	// 인벤토리 남은 자리 확인
	if (items.size() >= capacity)
	{
		return;
	}
	
	// 동일 아이템 확인
	for (const auto& item_ : items)
	{
		if (item_->GetItemInfo().name == itemName_)
		{
			// 개수 만큼 추가
			item_->AddItemCount(itemCount_);
			break;
		}
	}
	
	// 아이템 추가
	items.push_back(shared_ptr<Item>(Item_));
}

void Inventory::RemoveItem(const string& itemName_, const int& itemCount_)
{
	for (auto inventorySlot = items.begin(); inventorySlot != items.end(); )
	{
		auto& item_ = *inventorySlot; // item_ 타입 : shared_ptr<Item>&

		if (item_->GetItemInfo().name == itemName_)
		{
			// 개수 만큼 감소
			item_->ReduceItemCount(itemCount_);
			if (item_->GetiItemCount() <= 0)
			{
				inventorySlot = items.erase(inventorySlot);
			}
		}
	}
}


