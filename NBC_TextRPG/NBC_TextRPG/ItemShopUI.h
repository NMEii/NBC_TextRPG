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

class ItemShopUI : public BaseUI
{
public:
	ItemShopUI();

	ItemShopUI(Inventory* inInventory);

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

private: 
	UIRect scriptRect;
	UIRect menuRect;
	UIRect goldRect;
	UIRect inventoryRect;

	vector<UIRect> ItemRects;

	ItemShopState currentState = ItemShopState::ActionMenu; 

	vector<string> tempItems = { "a", "b", "c" };
	int itemSelectIndex = 0; 
	vector<string> itemActionMenu; 
	int itemActionIndex = 0; 

	int inventorySelctIndex = 0; 

	vector<string> inventoryActionMenu;
	int inventoryActionIndex = 0; 

	Inventory* inventory; 
};
 
