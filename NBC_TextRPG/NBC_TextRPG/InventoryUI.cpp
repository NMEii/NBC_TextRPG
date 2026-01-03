#include "pch.h"
#include "InventoryUI.h"
#include "Inventory.h"
#include "Player.h"

InventoryUI::InventoryUI(Inventory* inInventory)
{
	inventory = inInventory; 
	InitUI(); 
}

InventoryUI::InventoryUI()
{
	player = Player::GetInstance();
	if (player)
	{
		inventory = player->GetInventory();
	}

	InitUI(); 
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

	DrawInventoryRect();

	DrawScriptRect();
	// 선택지 출력 
	DrawMenuRect(); 
 
}

void InventoryUI::Update()
{
	switch (currentState)
	{
	case InventoryState::ActionMenu: 
		UpdateActionMenu(); 

		break;
		// 아이템 선택
	case InventoryState::ItemSelect: 
		UpdateItemSelect();

		break; 
		// 아이템 액션 선택 
	case InventoryState::ItemAction:
		UpdateItemAction();
 break; 

	}
}

void InventoryUI::OnSelect(int choice)
{
	// Action 

	if (choice == 0) // 아이템 선택 
	{
		ChangeState(InventoryState::ItemSelect);
	}
	else if (choice == 1 && OnRequest) // 나가기 
		OnRequest(UIRequest::OpenCombatUI);

}

void InventoryUI::InitUI()
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

void InventoryUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}

void InventoryUI::DrawTitleRect()
{
	DrawRect(titleRect);

	// 제목 
	SetCursorPos(titleRect.InnerX() + 40, titleRect.InnerY() + 1);
	PrintColorString(ColorType::DarkGray, "인벤토리");
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
		SetCursorPos(inventoryRect.InnerX() + 6, inventoryRect.InnerY()+3  + i * 2);
		if (currentState == InventoryState::ItemSelect || currentState == InventoryState::ItemAction)
		{
			if (i == itemSelectIndex)
				cout << "  ▶ " << "[" << i + 1 << "] " << tempitems[i];
			else
			{
				cout << "    [" << i +1 << "] ";
				PrintColorString(ColorType::DarkGray, tempitems[i]);
			}
		}
		else
		{
			cout << "    [" << i + 1 << "] ";
			PrintColorString(ColorType::WHITE, tempitems[i]);
		}
		
		
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
			SetCursorPos(menuRect.InnerX() + 3, menuRect.InnerY()+1 + i*2);
			if (i == selectedIndex)
			{
				cout << "  ▶ " << "[" << menus[i] << "]";
			}
			else
			{
				cout << "    ";
				PrintColorString(ColorType::DarkGray, menus[i]);
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
				cout << "    ";
				PrintColorString(ColorType::DarkGray, itemActionMenu[i]);
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

	SetCursorPos(scriptRect.InnerX()+3, scriptRect.InnerY());
	switch (currentState)
	{
	case InventoryState::ActionMenu:
		PrintColorString(ColorType::GRAY, "현재 " + player->stats.name + "이의 가방이다.");

		//cout << "현재 플레이어의 가방 상태입니다.";
		break;

	case InventoryState::ItemSelect:
		cout << "아이템을 선택하자";
		break;

	case InventoryState::ItemAction:
		cout << "이걸 어떻게 하지...";
		break; 
	}

	
}

void InventoryUI::DrawPlayerInfoRect()
{
	PlayerInfoRect = GetCenteredRect(20, 11); 
	PlayerInfoRect.x += 32;
	PlayerInfoRect.y += 2;

	DrawRect(PlayerInfoRect);

	SetCursorPos(PlayerInfoRect.InnerX() + 3, PlayerInfoRect.InnerY());
	cout << "플레이어 상태";
	
	SetCursorPos(PlayerInfoRect.InnerX() + 2, PlayerInfoRect.InnerY() + 2);
	cout << "이름 : " << player->stats.name;

	SetCursorPos(PlayerInfoRect.InnerX() + 2, PlayerInfoRect.InnerY() + 4);
	cout << "HP : " << player->stats.currentHealth << " / " << player->stats.maxHealth;
	SetCursorPos(PlayerInfoRect.InnerX() + 3, PlayerInfoRect.InnerY() + 6);
	cout << "ATK : " << player->stats.attack;
}

void InventoryUI::DrawGoldRect()
{
	GoldRect = GetCenteredRect(20, 6);
	GoldRect.x += 32; 
	GoldRect.y -= 7;
	DrawRect(GoldRect);

	SetCursorPos(GoldRect.InnerX() + 4, GoldRect.InnerY());
	PrintColorString(ColorType::GRAY, "현재 잔액");

	SetCursorPos(GoldRect.InnerX() + 10, GoldRect.InnerY() + 2);
	cout << inventory->gold;

	SetCursorPos(GoldRect.InnerX() + 15, GoldRect.InnerY() + 3);
	cout  << "원";
}

void InventoryUI::ChangeState(InventoryState newState, bool bShouldRest)
{
	currentState = newState;
	
	if (bShouldRest)
	{
		selectedIndex = 0;
		itemActionIndex = 0;
		itemSelectIndex = 0;
	}
}


void InventoryUI::UpdateActionMenu()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex);
	}
}

void InventoryUI::UpdateItemSelect()
{
	// 아이템 고르기 
	if (HandleKeyInput(itemSelectIndex, tempitems.size()))
	{
		// 아이템 선택 
		ChangeState(InventoryState::ItemAction, false);
	}
}

void InventoryUI::UpdateItemAction()
{
	if (HandleKeyInput(itemActionIndex, itemActionMenu.size()))
	{

		switch (itemActionIndex)
		{
		case 0: // 아이템 사용 

			// player->UseItem();

			break;

		case 1: // 아이템 버리기 

			// inventory->RemoveItem(); 

			break;

		case 2: // 취소 
			ChangeState(InventoryState::ActionMenu);
			break;
		}

	}
}