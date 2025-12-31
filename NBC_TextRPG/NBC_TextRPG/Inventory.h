#pragma once
#include <map>
#include "Item.h"
using namespace std;

class Item;

class Inventory
{
private:
	map<string, unique_ptr<Item>> mInventory;	// 인벤토리 저장소 key : n번슬롯, value : 아이템
	int capacity; // 인벤토리 용량

public:
	Inventory();	// 생성자
	~Inventory();	// 소멸자

	map<string, Item> GetInventory() const;	// Getter

	void AddItem(Item* Item_);	// 인벤토리에 아이템 추가
	void RemoveItem(const string& itemName_, const int& itemCount_);	// 인벤토리에 있는 아이템 삭제
	void ShowInventory();				// 인벤토리 내용 출력 -> 테스트용 함수
};

