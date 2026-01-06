#pragma once

using namespace std;

class Item;

class ItemTable
{
private:
	map<string, Item> table;

public:
	ItemTable(); 
	void Init();	// 아이템 등록
	Item* GetItem(const string& itemName);	// 아이템 불러오기

	Item* GetRandomItem(); 
};

