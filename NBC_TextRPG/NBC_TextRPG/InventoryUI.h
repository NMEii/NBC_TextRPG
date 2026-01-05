#pragma once
#include "BaseUI.h"

enum class InventoryState
{
	ActionMenu, // 아이템 선택, 나가기
	ItemSelect, // 인벤토리에서 아이템 선택
	ItemAction // 아이템 사용 / 버리기 / 취소 
};


class Inventory;
class Player; 

class InventoryUI : public BaseUI
{
public:

	InventoryUI(Inventory* inInventory);


	InventoryUI();

	~InventoryUI(); 

	// 화면 그리기 
	virtual void Render() override;

	// 화면 업데이트 
	virtual void Update() override;

	// 메뉴 선택 처리 
	void OnSelect(int choice) override;

private: 
	virtual void InitUI() override; 

protected:

	void DrawCanvasRect(); 

	void DrawTitleRect(); 

	void DrawInventoryRect(); 

	void DrawMenuRect();
	
	void DrawScriptRect();

	void DrawPlayerInfoRect(); 

	void DrawGoldRect(); 

protected:

	void UpdateActionMenu(); 

	void UpdateItemSelect();

	void UpdateItemAction();



protected:

	void ChangeState(InventoryState newState, bool bShouldRest = true); 

	//ItemUse
	void UseItemFromInventory();
	void DiscardItmeFromInventory();

private:

	UIRect scriptRect;
	UIRect menuRect;
	UIRect PlayerInfoRect; 
	UIRect inventoryRect; 
	UIRect GoldRect; 

	Inventory* inventory; 
	Player* player; 

	int itemActionIndex = 0;
	int itemSelectIndex = 0; 

	vector<string> itemActionMenu; 

	InventoryState currentState = InventoryState::ActionMenu; 

	


	// 임시 아이템 예시 
	vector<string> tempitems = { "a","b", "c", "d", "e", "f"};
};

