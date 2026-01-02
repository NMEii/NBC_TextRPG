#pragma once
#include "BaseUI.h"

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

private: 
	UIRect scriptRect;
	UIRect menuRect;
	UIRect GoldRect;
};
 
