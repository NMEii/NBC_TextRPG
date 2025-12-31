#include "pch.h"
#include "Inventory.h"

Inventory::Inventory() : capacity(10)
{
	vInventory.reserve(capacity);	// 인벤토리 최대용량 초기화
}

Inventory::~Inventory()
{
}

vector<shared_ptr<Item>> Inventory::GetInventory() const
{
	return vInventory;
}

void Inventory::AddItem(Item* Item_)
{
	string itemName_ = Item_->GetsItemName();

	// 인벤토리 남은 자리 확인
	if (vInventory.size() >= capacity)
	{
		return;
	}
	
	// 동일 아이템 확인
	for (const auto& item_ : vInventory)
	{
		if (item_->GetsItemName() == itemName_)
		{
			// 개수 만큼 추가
			item_->AddItemCount(Item_->GetiItemCount());
			break;
		}
	}
	
	// 아이템 추가
	vInventory.push_back(shared_ptr<Item>(Item_));
}

void Inventory::RemoveItem(const string& itemName_, const int& itemCount_)
{
	for (auto inventorySlot = vInventory.begin(); inventorySlot != vInventory.end(); )
	{
		auto& item_ = *inventorySlot; // item_ 타입 : shared_ptr<Item>&

		if (item_->GetsItemName() == itemName_)
		{
			// 개수 만큼 감소
			item_->ReduceItemCount(itemCount_);
			if (item_->GetiItemCount() <= 0)
			{
				inventorySlot = vInventory.erase(inventorySlot);
			}
		}
	}
}


