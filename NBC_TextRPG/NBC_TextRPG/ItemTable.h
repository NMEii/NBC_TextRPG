#pragma once

using namespace std;

class Item;

class ItemTable
{
private:
	map<string, Item*> table;

public:
	void Init();	// 아이템 등록
	Item* GetItem(string itemName) const;	// 아이템 불러오기
};

