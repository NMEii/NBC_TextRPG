#include "pch.h"
#include "ItemShopUI.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"

ItemShopUI::ItemShopUI()
{	
	InitUI(); 
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
	DrawItemRects();
	DrawInventoryRect();
}

void ItemShopUI::Update()
{
	switch (currentState)
	{
	case ItemShopState::ActionMenu:
		UpdateActionMenu();
		break;

	case ItemShopState::ItemSelect:
		UpdateItemSelect();
		break;

	case ItemShopState::ItemAction:
		UpdateItemAction();
		break;

	case ItemShopState::InventorySelect:
		UpdateInventorySelect();
		break;

	case ItemShopState::InventoryAction:
		UpdateInventoryAction();
		break;
	}

}

void ItemShopUI::OnSelect(int choice)
{
	switch (choice)
	{
	case 0: // 아이템 구매 
		ChangeState(ItemShopState::ItemSelect);
		break;

	case 1:  // 아이템 판매 
		ChangeState(ItemShopState::InventorySelect);
		break; 

	case 2: // 상점 나가기 
		if (OnRequest)
			OnRequest(UIRequest::OpenCombatUI);
		
		break; 
	}

}


void ItemShopUI::InitUI()
{
	menus = {
		"아이템 구매",
		"판매",
		"나가기"
	};

	itemActionMenu = {
		"구매",
		"취소"
	};

	inventoryActionMenu = {
		"판매",
		"취소"
	};

	ItemRects = vector<UIRect>(3);

	for (int i = 0; i < ItemRects.size(); i++)
	{
		ItemRects[i] = GetCenteredRect(20, 6);
		ItemRects[i].x = canvasRect.x + 10 + 25 * i;
	}

	inventoryRect = GetCenteredRect(20, 11);
	inventoryRect.x += 32;
	inventoryRect.y += 2;

	player = Player::GetInstance(); 
	if (player)
	{
		inventory = player->GetInventory();

		items = inventory->GetItemList();
	}
	
	// 임시 코드 
	items = { "a" , "b", "c" , "d", "e", "f"};
}

void ItemShopUI::DrawCanvasRect()
{
	DrawRect(canvasRect);

}
void ItemShopUI::DrawTitleRect()
{
	DrawRect(titleRect); 

	SetCursorPos(titleRect.InnerX() + 40, titleRect.InnerY() + 1);
	cout << "아이템 상점";
}


void ItemShopUI::DrawMenuRect()
{
	menuRect = GetCenteredRect(30, 8);
	menuRect.x += 30;
	menuRect.y += 11;
 
	DrawRect(menuRect);

	switch (currentState)
	{
	case ItemShopState::ActionMenu:

		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 3, menuRect.InnerY() + 1 + i);
			if (i == selectedIndex)
			{
				cout << "  ▶ " << "[" << menus[i] << "]";
			}
			else
			{
				cout << "    ";
				PrintColorString(ColorType::DarkGray,menus[i]);
			}
		}

		break; 
		
	case ItemShopState::ItemAction:

		for (int i = 0; i < itemActionMenu.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 3, menuRect.InnerY() + 1 + i);
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

		break; 


	case ItemShopState::InventoryAction:

		for (int i = 0; i < inventoryActionMenu.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 3, menuRect.InnerY() + 1 + i);
			if (i == inventoryActionIndex)
			{
				cout << "  ▶ " << "[" << inventoryActionMenu[i] << "]";
			}
			else
			{
				cout << "    ";
				PrintColorString(ColorType::DarkGray, inventoryActionMenu[i]);
			}
		}

		break; 
	}


}

void ItemShopUI::DrawScriptRect()
{
	scriptRect = GetCenteredRect(60, 8);
	scriptRect.x = canvasRect.x;
	scriptRect.y += 11;

	DrawRect(scriptRect);

	SetCursorPos(scriptRect.InnerX() + 3, scriptRect.InnerY());

	switch (currentState)
	{
	case ItemShopState::ActionMenu:
		if (player)
			cout << "어서오세요, " << player->stats.name << "님. 무엇을 하시겠어요 ? ";
		break; 
	case ItemShopState::ItemSelect:
		cout << "구매하실 아이템을 선택해주세요.";
		break; 
	case ItemShopState::ItemAction:
		cout << "이 아이템을 구매하시겠어요?";
		break; 
	case ItemShopState::InventorySelect:
		cout << "판매할 아이템을 선택해주세요.";
	}
}

void ItemShopUI::DrawGoldRect()
{
	goldRect = GetCenteredRect(20, 6);
	goldRect.x += 32;
	goldRect.y -= 7;
	DrawRect(goldRect);

	SetCursorPos(goldRect.InnerX() + 4, goldRect.InnerY());
	cout << "현재 잔액";

	SetCursorPos(goldRect.InnerX() + 8, goldRect.InnerY() + 2);
	if(inventory)
		cout << inventory->gold; 

	SetCursorPos(goldRect.InnerX() + 15, goldRect.InnerY() + 3);
	cout << "원";
}

void ItemShopUI::DrawItemRects()
{
	for (int i = 0; i < ItemRects.size(); i++)
	{
		DrawRect(ItemRects[i]);

		SetCursorPos(ItemRects[i].InnerX()+4, ItemRects[i].InnerY());
		
		if (currentState == ItemShopState::ItemSelect || currentState == ItemShopState::ItemAction)
		{
			if (i == itemSelectIndex)
			{
				cout << "  ▶ [";
				PrintColorString(ColorType::SkyBlue, tempItems[i]);
				cout << "]";
			}
			else
			{
				PrintColorString(ColorType::DarkGray, tempItems[i]);
			}
		}
		else
		{
			PrintColorString(ColorType::SkyBlue, tempItems[i]);
		}
		
	}
}


void ItemShopUI::DrawInventoryRect()
{
	
	if (currentState == ItemShopState::InventorySelect ||
		currentState == ItemShopState::InventoryAction)
	{
		DrawRect(inventoryRect);

		if (items.empty())
		{
			SetCursorPos(inventoryRect.InnerX(), inventoryRect.InnerY() + 4);
			cout << "아이템이 없습니다.";
			return;
		}
		
		for (int i = 0; i < items.size(); i++)
		{
			if (i == inventorySelctIndex)
			{
				SetCursorPos(inventoryRect.InnerX() +2, inventoryRect.InnerY() + 1 + i);
				cout << "  ▶ " << "[" << items[i] << "]";
			}
			else
			{
				SetCursorPos(inventoryRect.InnerX() + 7, inventoryRect.InnerY() + 1 + i);
				PrintColorString(ColorType::DarkGray, items[i]);
			}
		}
	}
}

void ItemShopUI::ChangeState(ItemShopState newState, bool bShouldReset)
{
	currentState = newState; 

	if (bShouldReset)
	{
		selectedIndex = 0;
		itemSelectIndex = 0;
		inventoryActionIndex = 0;
		inventorySelctIndex = 0;
	}

}

void ItemShopUI::UpdateActionMenu()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex);
	}
}

void ItemShopUI::UpdateItemSelect()
{
	if (HandleKeyInput(itemSelectIndex, tempItems.size(), false))
	{
		// 아이템 선택 
		ChangeState(ItemShopState::ItemAction, false);
	}
}

void ItemShopUI::UpdateItemAction()
{
	if (HandleKeyInput(itemActionIndex, itemActionMenu.size()))
	{
		switch (itemActionIndex)
		{
		case 0: // 아이템 구매 

			// 플레이어 골드 체크 

			// 골드 차감 및 아이템 추가 

			break;
		case 1: // 취소 
			ChangeState(ItemShopState::ActionMenu);
			break;
		}
	}
}

void ItemShopUI::UpdateInventorySelect()
{
	if (items.empty())
	{
		ChangeState(ItemShopState::ActionMenu);
	}

	if (HandleKeyInput(inventorySelctIndex, items.size()))
	{
		ChangeState(ItemShopState::InventoryAction, false);
	}
}

void ItemShopUI::UpdateInventoryAction()
{
	if (HandleKeyInput(inventoryActionIndex, inventoryActionMenu.size()))
	{
		switch (inventoryActionIndex)
		{
		case 0: // 판매

			break;
		case 1: // 취소 
			ChangeState(ItemShopState::ActionMenu);

			break;
		}
	}
}
