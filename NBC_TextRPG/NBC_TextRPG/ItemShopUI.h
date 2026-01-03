#pragma once
#include "BaseUI.h"

using namespace std; 

enum class ItemShopState
{
	ActionMenu,
	ItemSelect, 
	ItemAction,
	InventorySelect, 
	InventoryAction, 
};

class Inventory; 
class Player; 

class ItemShopUI : public BaseUI
{
public:
	ItemShopUI();

	~ItemShopUI(); 

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
	void DrawMenuRect();
	void DrawScriptRect();
	void DrawGoldRect(); 

	void DrawItemRects();
	void DrawInventoryRect(); 


protected:
	void ChangeState(ItemShopState newState); 

protected:
	void UpdateActionMenu(); 

	void UpdateItemSelect(); 

	void UpdateItemAction(); 
	
	void UpdateInventorySelect(); 

	void UpdateInventoryAction(); 

private: 
	UIRect scriptRect;
	UIRect menuRect;
	UIRect goldRect;
	UIRect inventoryRect;

	vector<UIRect> ItemRects;

	ItemShopState currentState = ItemShopState::ActionMenu; 

	Player* player; 

	vector<string> tempItems = { "a", "b", "c" };
	int itemSelectIndex = 0; 
	vector<string> itemActionMenu; 
	int itemActionIndex = 0; 

	

	vector<string> inventoryActionMenu;
	int inventoryActionIndex = 0; 

	Inventory* inventory; 

	vector<string> items;
	int inventorySelctIndex = 0;
};
 
