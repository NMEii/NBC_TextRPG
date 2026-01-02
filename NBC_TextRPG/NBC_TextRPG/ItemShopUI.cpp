#include "pch.h"
#include "ItemShopUI.h"

ItemShopUI::ItemShopUI()
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
	ItemRects = vector<UIRect>(3);
	
	for (int i = 0; i < ItemRects.size(); i++)
	{
		ItemRects[i] = GetCenteredRect(20, 6);
		ItemRects[i].x = canvasRect.x + 10 + 25 * i;
	}

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

		break; 
	case 2: // 상점 나가기 

		if (OnRequest)
		{
			OnRequest(UIRequest::OpenCombatUI);
		}
		break; 
	}

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

	if (currentState == ItemShopState::ActionMenu)
	{
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
	}
	else if (currentState == ItemShopState::ItemAction)
	{
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
	GoldRect = GetCenteredRect(20, 6);
	GoldRect.x += 32;
	GoldRect.y -= 7;
	DrawRect(GoldRect);

	SetCursorPos(GoldRect.InnerX() + 4, GoldRect.InnerY());
	cout << "현재 잔액";

	SetCursorPos(GoldRect.InnerX() + 15, GoldRect.InnerY() + 3);
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
