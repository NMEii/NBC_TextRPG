#pragma once
#include "BaseUI.h"

using namespace std; 

enum class ItemShopState
{
	ActionMenu,
	ItemSelect, 
	ItemAction
};

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

protected:
	void DrawCanvasRect();
	void DrawTitleRect();
	void DrawMenuRect();
	void DrawScriptRect();
	void DrawGoldRect(); 

	void DrawItemRects();

private: 
	UIRect scriptRect;
	UIRect menuRect;
	UIRect GoldRect;

	vector<UIRect> ItemRects;

	ItemShopState currentState = ItemShopState::ActionMenu; 

	vector<string> tempItems = { "a", "b", "c" };
	int itemSelectIndex = 0; 
	vector<string> itemActionMenu; 
	int itemActionIndex = 0; 
};
 
