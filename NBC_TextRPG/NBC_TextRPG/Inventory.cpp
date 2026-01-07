#include "pch.h"
#include "Inventory.h"
#include "Item.h"
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
	nameList.reserve(items.size());

	for (const auto& data : items)
	{
		nameList.push_back(data->GetItemInfo().name);
	}

	return nameList;
}

void Inventory::AddItem(Item* Item_, const int itemCount_)
{
	if (!Item_)
		return;

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
			item_->IncreaseCount(itemCount_);
			return;
		}
	}

	// 아이템 추가
	items.push_back(make_shared<Item>(*Item_));
	items.back()->SetsItemCount(itemCount_);
}

bool Inventory::RemoveItem(const string& itemName_, const int& itemCount_)
{
	auto it = find_if(items.begin(), items.end(), [itemName_](shared_ptr<Item> item) 
		{ return item->GetItemInfo().name == itemName_; }
	);

	// 아이템이 없는 경우 
	if (it == items.end()) return false;

	// 아이템은 있으나 개수가 0개이하 인 경우 
	int itemCount = it->get()->GetiItemCount();
	if (itemCount <= 0) return false;

	it->get()->ReduceItemCount(itemCount_);

	return true; 
}

int Inventory::GetItemPriceByName(const string& name)
{
	auto it = find_if(items.begin(), items.end(), [name](shared_ptr<Item> item)
		{ return item->GetItemInfo().name == name; }
	);

	if (it == items.end()) return 0;

	return it->get()->GetItemInfo().price;
}


