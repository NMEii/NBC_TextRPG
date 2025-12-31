#include "pch.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	menus = {
		"아이템 선택",
		"나가기"
	};
	scriptRect = GetCenteredRect(40, 6);
	scriptRect.x -= 10;
	scriptRect.y += 7;

	menuRect = GetCenteredRect(20, 6);
	menuRect.x += 20;
	menuRect.y += 7;
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Render()
{

	ClearConsole();
	DrawRect(canvasRect);
	DrawRect(TitleRect);

	DrawRect(scriptRect);
	DrawRect(menuRect); 

	SetCursorPos(TitleRect.InnerX() + 26, TitleRect.InnerY() + 1);
	cout << "인벤토리";
	
	// 아이템 리스트 출력 

	

	// 메뉴 그리기 
	for (int i = 0; i < menus.size(); i++)
	{
		SetCursorPos(menuRect.InnerX(), menuRect.InnerY()+1 + i);
		if (i == selectedIndex)
		{
			cout << "  ▶ " << "[" << menus[i] << "]";
		}

		else
		{
			cout << "    " << menus[i];
		}
	}
	

}

void InventoryUI::Update()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex); 
	}

}

void InventoryUI::OnSelect(int choice)
{
	if (choice == 0)
	{

	}
	else if (choice == 1 && OnRequest)
		OnRequest(UIRequest::OpenCombatUI);

}
