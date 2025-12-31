#include "pch.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	menus = {
		"아이템 선택",
		"나가기"
	};

	itemActionMenu = {
		"사용",
		"버리기", 
		"취소"
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

	canvasRect = GetCenteredRect(60, 18); 

	DrawRect(canvasRect);
	DrawRect(titleRect);
	DrawRect(scriptRect);

	// 제목 
	SetCursorPos(titleRect.InnerX() + 26, titleRect.InnerY() + 1);
	cout << "인벤토리";
	
	// Todo 
	// 아이템 리스트 출력 
	DrawInventoryRect();


	// 선택지 출력 
	DrawMenuRect(); 
	
}

void InventoryUI::Update()
{
	switch (currentState)
	{
	case InventoryState::ActionMenu: // 액션 선택 
		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}
		break;

	case InventoryState::ItemSelect: // 아이템 선택 

		// Todo : 인벤토리에 연결해야함. 
		// 아이템 고르기 
		if (HandleKeyInput(itemSelectIndex, tempitems.size()))
		{
			// 아이템 선택 

			currentState = InventoryState::ItemAction; 
		}
		break;

	case InventoryState::ItemAction: // 아이템 액션 선택 

		if (HandleKeyInput(itemActionIndex, itemActionMenu.size()))
		{

			switch (itemActionIndex)
			{
			case 0: // 아이템 사용 
				break;

			case 1: // 아이템 버리기 
				break;

			case 2: // 취소 
				currentState = InventoryState::ActionMenu;
				break; 
			}
			
		}

		break; 
	}


}

void InventoryUI::OnSelect(int choice)
{
	// Action 

	if (choice == 0) // 아이템 선택 
	{
		currentState = InventoryState::ItemSelect;
	}
	else if (choice == 1 && OnRequest) // 나가기 
		OnRequest(UIRequest::OpenCombatUI);

}

void InventoryUI::DrawInventoryRect()
{
	// 인벤토리에 있는 
	for (int i = 0; i < tempitems.size(); i++)
	{
		SetCursorPos(titleRect.InnerX() + 5, titleRect.InnerY() + 5 + i * 2);
		if (currentState == InventoryState::ItemSelect &&
			i == itemSelectIndex)
			cout << "  ▶ ";

		cout << "[" << i + 1 << "]" << tempitems[i];

	}
}

void InventoryUI::DrawMenuRect()
{
	// 메뉴 박스 그리기 
	DrawRect(menuRect);

	if (currentState == InventoryState::ActionMenu)
	{
		// 메뉴 그리기 
		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX(), menuRect.InnerY() + i);
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
	else if (currentState == InventoryState::ItemAction)
	{
		// 아이템 선택된 경우 

		for (int i = 0; i < itemActionMenu.size(); i++)
		{
			SetCursorPos(menuRect.InnerX(), menuRect.InnerY() + 1 + i);
			if (i == itemActionIndex)
			{
				cout << "  ▶ " << "[" << itemActionMenu[i] << "]";
			}

			else
			{
				cout << "    " << itemActionMenu[i];
			}
		}
	}

	
}
