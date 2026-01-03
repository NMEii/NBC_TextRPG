#include "pch.h"
#include "ItemShopUI.h"
#include "Inventory.h"
#include "Item.h"

ItemShopUI::ItemShopUI()
{
	
	InitUI(); 
}

ItemShopUI::ItemShopUI(Inventory* inInventory)
{
	inventory = inInventory;
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
		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}

		break; 
	case ItemShopState::ItemSelect:
		if (HandleKeyInput(itemSelectIndex, tempItems.size(), false))
		{
			// 아이템 선택 

			currentState = ItemShopState::ItemAction;
		}
		break; 

	case ItemShopState::ItemAction:
		if (HandleKeyInput(itemActionIndex, itemActionMenu.size()))
		{
			switch (itemActionIndex)
			{
			case 0: // 아이템 구매 

				break;
			case 1: // 취소 
				currentState = ItemShopState::ActionMenu;
				itemActionIndex = 0;
				break; 
			}
		}
		break;

	case ItemShopState::InventorySelect:

		break;

	case ItemShopState::InventoryAction:

		break;
	}

}

void ItemShopUI::OnSelect(int choice)
{
	switch (choice)
	{
	case 0: // 아이템 구매 

		currentState = ItemShopState::ItemSelect;

		break;

	case 1:  // 아이템 판매 
		currentState = ItemShopState::InventorySelect;

		break; 
	case 2: // 상점 나가기 

		if (OnRequest)
		{
			OnRequest(UIRequest::OpenCombatUI);
		}
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
		"선택",
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

	// 메뉴 박스 그리기 
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
				cout << "    " << menus[i];
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
				cout << "    " << itemActionMenu[i];
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
				cout << "    " << inventoryActionMenu[i];
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
		cout << "어서오세요, 병권님.  무엇을 하시겠어요?";
		break; 
	case ItemShopState::ItemSelect:
		cout << "구매하실 아이템을 선택해주세요.";
		break; 
	case ItemShopState::ItemAction:
		cout << "이 아이템을 구매하시겠어요?";
		break; 
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
		
		if ((currentState == ItemShopState::ItemSelect || currentState == ItemShopState::ItemAction) 
			&&i == itemSelectIndex)
		{
			cout << "  ▶ " << "[" << tempItems[i] << "]";
		}
		else
		{
			cout << tempItems[i];
		}
		
	}
}


void ItemShopUI::DrawInventoryRect()
{
	
	if (currentState == ItemShopState::InventorySelect ||
		currentState == ItemShopState::InventoryAction)
	{
		DrawRect(inventoryRect);

		auto items = inventory->GetItemList();

		if (items.empty())
		{
			SetCursorPos(inventoryRect.InnerX(), inventoryRect.InnerY() + 4);
			cout << "아이템이 없습니다.";
			return;
		}
		
		for (int i = 0; i < items.size(); i++)
		{
			SetCursorPos(inventoryRect.InnerX(), inventoryRect.InnerY() +i);
			cout << items[i];
		}
	}
}