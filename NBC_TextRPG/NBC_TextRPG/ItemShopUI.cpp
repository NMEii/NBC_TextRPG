#include "pch.h"
#include "ItemShopUI.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ItemTable.h"

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
	DrawKeyRect(); 
	DrawItemScriptRect();
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

	ItemTable* table = new ItemTable();

	for (int i = 0; i < 3; i++)
	{
		Item* item = table->GetRandomItem();
		sellingItems.push_back(item);
	}

	for (int i = 0; i < ItemRects.size(); i++)
	{
		ItemRects[i] = GetCenteredRect(20, 6);
		ItemRects[i].x = canvasRect.x + 10 + 25 * i;
	}

	inventoryRect = GetCenteredRect(20, 11);
	inventoryRect.x += 32;
	inventoryRect.y += 2;

	keyRect = GetCenteredRect(27, 3);
	keyRect.y += 6; 

	itemScriptRect = GetCenteredRect(52, 7); 
	itemScriptRect.x -= 10;
	itemScriptRect.y -= 6; 

	player = Player::GetInstance(); 
	if (player)
	{
		inventory = player->GetInventory();;
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
	PrintColorString(ColorType::DarkGray, "아이템 상점");
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

		if (inventory->GetInventory().empty())return;

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
	string name; 
	int price = 0; 
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
		break; 

	case ItemShopState::InventoryAction:

		if (!inventory->GetInventory().empty())
		{
			name = inventory->GetInventory()[inventorySelctIndex]->GetItemInfo().name; 
			price = (4 * inventory->GetInventory()[inventorySelctIndex]->GetItemInfo().price) / 10;
			
			PrintColorString(ColorType::Gray, name);
			PrintColorString(ColorType::White, "을 판매하시겠어요?");

			SetCursorPos(scriptRect.InnerX() + 20, scriptRect.InnerY() + 1);
			PrintColorString(ColorType::Blue, "[" +to_string(price) + " 원]");
		}
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

	
		SetCursorPos(ItemRects[i].InnerX() + 4, ItemRects[i].InnerY());
		if (currentState == ItemShopState::ItemSelect || currentState == ItemShopState::ItemAction)
		{
			if (i == itemSelectIndex)
			{
				SetCursorPos(ItemRects[i].InnerX(), ItemRects[i].InnerY());
				cout << "  ▶ [";
				PrintColorString(ColorType::SkyBlue, sellingItems[i]->GetItemInfo().name);
				cout << "]";
			}
			else
			{

				PrintColorString(ColorType::DarkGray, sellingItems[i]->GetItemInfo().name);
			}
		}
		else
		{
			PrintColorString(ColorType::SkyBlue, sellingItems[i]->GetItemInfo().name);
		}
		
	}
}


void ItemShopUI::DrawInventoryRect()
{
	
	if (currentState == ItemShopState::InventorySelect ||
		currentState == ItemShopState::InventoryAction)
	{
		DrawRect(inventoryRect);

		if (inventory->GetInventory().empty())
		{
			SetCursorPos(inventoryRect.InnerX(), inventoryRect.InnerY() + 4);
			cout << "아이템이 없습니다.";
			return;
		}
		
		for (int i = 0; i < inventory->GetInventory().size(); i++)
		{

			int itemCount = inventory->GetInventory()[i]->GetiItemCount();
			if (i == inventorySelctIndex)
			{
				SetCursorPos(inventoryRect.InnerX(), inventoryRect.InnerY() + 1 + i);
				cout << "  ▶ " << "[" << inventory->GetInventory()[i]->GetItemInfo().name << "x" << itemCount << "]";
			}
			else
			{
				SetCursorPos(inventoryRect.InnerX()+3 , inventoryRect.InnerY() + 1 + i);
				PrintColorString(ColorType::DarkGray, inventory->GetInventory()[i]->GetItemInfo().name + " x" + to_string(itemCount));
			}
		}
	}
}

void ItemShopUI::DrawItemScriptRect()
{
	if (currentState == ItemShopState::ItemSelect || currentState == ItemShopState::ItemAction)
	{
		DrawRect(itemScriptRect);
		if (itemSelectIndex < sellingItems.size())
		{
			SetCursorPos(itemScriptRect.InnerX() + 18, itemScriptRect.InnerY());
			PrintColorString(ColorType::White, "[" + sellingItems[itemSelectIndex]->GetItemInfo().name + "]");
			PrintColorString(ColorType::Gray, "(" + to_string(sellingItems[itemSelectIndex]->GetItemInfo().price) + "원)");

			SetCursorPos(itemScriptRect.InnerX() + 5, itemScriptRect.InnerY()+2);
			PrintColorString(ColorType::DarkGray, sellingItems[itemSelectIndex]->GetItemInfo().itemScript);
		}
	}
}

void ItemShopUI::DrawKeyRect()
{

	if (currentState == ItemShopState::ItemSelect)
	{
		DrawRect(keyRect);
		SetCursorPos(keyRect.InnerX()+2, keyRect.InnerY());
		PrintColorString(ColorType::DarkGray, "← → 이동 / Enter 선택");
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
	if (HandleKeyInput(itemSelectIndex,3, false))
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
			if (inventory->gold >= sellingItems[itemSelectIndex]->GetItemInfo().price)
			{
				// 골드 차감 
				inventory->gold -= sellingItems[itemSelectIndex]->GetItemInfo().price;
				SetCursorPos(itemScriptRect.InnerX(), itemScriptRect.InnerY());
				

				// 아이템 추가 

				inventory->AddItem(sellingItems[itemSelectIndex], 1);

				ClearRect(scriptRect);
				SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

				PrintColorString(ColorType::Yellow,
					sellingItems[itemSelectIndex]->GetItemInfo().name +
					"을/를 구매했습니다.");

				Delay(0.7f);
			}
			else
			{
				ClearRect(scriptRect);
				
				SetCursorPos(scriptRect.InnerX()+ 4, scriptRect.InnerY());
				PrintColorString(ColorType::Red,"잔액이 부족합니다.");

				Delay(1.0f);
			}

			break;
		case 1: // 취소 
			ChangeState(ItemShopState::ActionMenu);
			break;
		}
	}
}

void ItemShopUI::UpdateInventorySelect()
{
	if (inventory->IsEmpty())
	{
		Delay(0.6f);
		ChangeState(ItemShopState::ActionMenu);
		return;
	}

	if (HandleKeyInput(inventorySelctIndex, inventory->GetInventory().size()))
	{
		ChangeState(ItemShopState::InventoryAction, false);
	}
}

void ItemShopUI::UpdateInventoryAction()
{

	if (inventory->GetInventory().empty())
	{
		ChangeState(ItemShopState::ActionMenu);
		return;
	}

	if (HandleKeyInput(inventoryActionIndex, inventoryActionMenu.size()))
	{
		if (inventoryActionIndex == 0)
		{
			string itemName = inventory->GetInventory()[inventorySelctIndex]->GetItemInfo().name;
			int value = inventory->GetInventory()[inventorySelctIndex]->GetItemInfo().price;
			inventory->RemoveItem(itemName, 1);
			inventory->gold += (value*4) / 10; 

			ClearRect(scriptRect);
			SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
			PrintColorString(ColorType::Red, itemName);
			PrintColorString(ColorType::White, "을 판매했습니다.");
			Delay(0.7f);
		}
		else if (inventoryActionIndex == 1)
		{
			ChangeState(ItemShopState::ActionMenu);
		}

	}
}
