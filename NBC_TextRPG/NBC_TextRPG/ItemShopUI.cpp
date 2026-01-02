#include "pch.h"
#include "ItemShopUI.h"

ItemShopUI::ItemShopUI()
{
	menus = {
		"아이템 선택",
		"나가기"
	};
}

ItemShopUI::~ItemShopUI()
{
}

void ItemShopUI::Render()
{
	DrawCanvasRect(); 
	DrawTitleRect(); 
	DrawMenuRect(); 
	DrawScriptRect(); 
	DrawGoldRect();
}

void ItemShopUI::Update()
{
}

void ItemShopUI::OnSelect(int choice)
{
}


void ItemShopUI::DrawCanvasRect()
{
	DrawRect(canvasRect);

}
void ItemShopUI::DrawTitleRect()
{
	DrawRect(titleRect); 
}


void ItemShopUI::DrawMenuRect()
{
	menuRect = GetCenteredRect(30, 8);
	menuRect.x += 30;
	menuRect.y += 11;

	// 메뉴 박스 그리기 
	DrawRect(menuRect);
}

void ItemShopUI::DrawScriptRect()
{
	scriptRect = GetCenteredRect(60, 8);
	scriptRect.x = canvasRect.x;
	scriptRect.y += 11;

	DrawRect(scriptRect);
}

void ItemShopUI::DrawGoldRect()
{
	GoldRect = GetCenteredRect(20, 6);
	GoldRect.x += 32;
	GoldRect.y -= 7;
	DrawRect(GoldRect);

	SetCursorPos(GoldRect.InnerX() + 4, GoldRect.InnerY());
	cout << "현재 잔액";

	SetCursorPos(GoldRect.InnerX() + 15, GoldRect.InnerY() + 3);
	cout << "원";
}