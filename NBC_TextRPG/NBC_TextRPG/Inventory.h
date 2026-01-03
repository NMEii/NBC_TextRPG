#pragma once

using namespace std;

class Item;

class Inventory
{
private:
	vector<shared_ptr<Item>> items;		// 인벤토리 저장소
	int capacity; // 인벤토리 용량

public:
	int gold; 

public:
	Inventory();	// 생성자
	~Inventory();	// 소멸자

	vector<shared_ptr<Item>> GetInventory() const;	// Getter

	vector<string> GetItemList();	// 아이템 리스트



	void AddItem(Item* Item_, const int& itemCount_);	// 인벤토리에 아이템 추가
	void RemoveItem(const string& itemName_, const int& itemCount_);	// 인벤토리에 있는 아이템 삭제
};

