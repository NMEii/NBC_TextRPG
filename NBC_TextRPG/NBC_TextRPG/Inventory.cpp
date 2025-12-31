#include "pch.h"
#include "Inventory.h"

Inventory::Inventory() : capacity(10)
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(Item* Item_)
{
	string itemName_ = Item_->GetsItemName();
	
	// 인벤토리 남은 자리 확인
	if (mInventory.size() >= capacity)
	{
		return;
	}

	// 동일 아이템 확인
	if (mInventory.count(itemName_))
	{
		// 개수 만큼 추가
		mInventory[itemName_]->AddItemCount(Item_->GetiItemCount());	
	}
	
	// 아이템 추가
	mInventory.emplace(itemName_, unique_ptr<Item>(Item_));
}

void Inventory::RemoveItem(const string& itemName_, const int& itemCount_)
{
	//string itemName_ = Item_->GetsItemName();

	if (mInventory.count(itemName_))
	{
		// 개수 만큼 감소
		mInventory[itemName_]->ReduceItemCount(itemCount_);

		if (mInventory.find(itemName_)->second->GetiItemCount() <= 0)
		{
			mInventory.erase(itemName_);
		}
	}
}


void Inventory::ShowInventory()
{
	for (auto& item_ : mInventory)
	{
		cout << item_.second->GetsItemName() << ", ";
		cout << item_.second->GetiPrice() << "G ";
		cout << item_.second->GetiItemCount() << endl;
	}
}


