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


	
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Render()
{

	ClearConsole();

	DrawCanvasRect(); 

	DrawTitleRect(); 

	DrawPlayerInfoRect();
	DrawGoldRect();
	
	// Todo 
	// 아이템 리스트 출력 
	DrawInventoryRect();

	DrawScriptRect();
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

void InventoryUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}

void InventoryUI::DrawTitleRect()
{
	DrawRect(titleRect);

	// 제목 
	SetCursorPos(titleRect.InnerX() + 26, titleRect.InnerY() + 1);
	cout << "인벤토리";
}

void InventoryUI::DrawInventoryRect()
{
	inventoryRect = GetCenteredRect(62,17); 
	inventoryRect.x -= 12;
	inventoryRect.y -= 1;
	DrawRect(inventoryRect);

	// 인벤토리에 있는 
	for (int i = 0; i < tempitems.size(); i++)
	{
		SetCursorPos(inventoryRect.InnerX() + 3, inventoryRect.InnerY()+3  + i * 2);
		if (currentState == InventoryState::ItemSelect &&
			i == itemSelectIndex)
			cout << "  ▶ ";

		cout << "[" << i + 1 << "]" << tempitems[i];

	}
}

void InventoryUI::DrawMenuRect()
{
	menuRect = GetCenteredRect(30, 8);
	menuRect.x += 30;
	menuRect.y += 11;

	// 메뉴 박스 그리기 
	DrawRect(menuRect);

	if (currentState == InventoryState::ActionMenu)
	{
		// 메뉴 그리기 
		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 4, menuRect.InnerY()+1 + i*2);
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
			SetCursorPos(menuRect.InnerX()+7, menuRect.InnerY() + 1 + i*2);
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

void InventoryUI::DrawScriptRect()
{
	scriptRect = GetCenteredRect(60, 8);
	scriptRect.x = canvasRect.x;
	scriptRect.y += 11;

	DrawRect(scriptRect);
}

void InventoryUI::DrawPlayerInfoRect()
{
	PlayerInfoRect = GetCenteredRect(20, 11); 
	PlayerInfoRect.x += 32;
	PlayerInfoRect.y += 2;

	DrawRect(PlayerInfoRect);

	SetCursorPos(PlayerInfoRect.InnerX() + 3, PlayerInfoRect.InnerY());
	cout << "플레이어 상태";
}

void InventoryUI::DrawGoldRect()
{
	GoldRect = GetCenteredRect(20, 5);
	GoldRect.x += 32; 
	GoldRect.y -= 3;
	DrawRect(GoldRect);
}


