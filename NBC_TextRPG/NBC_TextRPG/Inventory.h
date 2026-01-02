#pragma once
#include <map>
#include "Item.h"
using namespace std;

class Item;

class Inventory
{
private:
	vector<shared_ptr<Item>> items;		// 인벤토리 저장소
	int capacity; // 인벤토리 용량

public:
	Inventory();	// 생성자
	~Inventory();	// 소멸자

	vector<shared_ptr<Item>> GetInventory() const;	// Getter

	void UseItem();
	void AddItem(Item* Item_);	// 인벤토리에 아이템 추가
	void RemoveItem(const string& itemName_, const int& itemCount_);	// 인벤토리에 있는 아이템 삭제
};

