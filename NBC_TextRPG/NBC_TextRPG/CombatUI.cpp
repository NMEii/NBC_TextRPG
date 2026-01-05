#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ItemTable.h"
#include "Inventory.h"

using namespace std; 

CombatUI::CombatUI()
{
	InitUI(); 
	monster = make_shared<Monster>("Mon", player->GetLevel(), 0);
}

CombatUI::~CombatUI()
{
}

void CombatUI::Render()
{
	ClearConsole();

	DrawCanvasRect();
	DrawMonster();

	DrawMonster();
	
	DrawTitleRect();

	DrawScriptRect();

	DrawMenuRect();

	DrawInfoRects();
}

void CombatUI::Update()
{
	switch (currentState)
	{
	case CombatUIState::Command:
		UpdateCommand(); 
		break; 
	case CombatUIState::SkillSelect: 
		UpdateSkillSelect(); 
		break;
	case CombatUIState::Result:
		UpdateResult(); 
		break; 
	case CombatUIState::Battle:
		UpdateBattle();
		break;
	}
}

void CombatUI::OnSelect(int choice)
{
	switch (choice)
	{
		// 싸운다 
	case 0: 
		ChangeState(CombatUIState::SkillSelect); 
		break;
		// 인벤토리
	case 1: if (OnRequest)
		OnRequest(UIRequest::OpenInventoryUI); 
		break;
		// 상점 
	case 2: if (OnRequest)
		OnRequest(UIRequest::OpenStoreUI);
		break;
		// 나가기 
	case 3: if (OnRequest)OnRequest(UIRequest::OpenMainMenu); break;
	}
}

void CombatUI::InitUI()
{
	menus =
	{
		"싸운다",
		"인벤토리",
		"상점",
		"나가기",
	};

	// 예시 
	tempSkills =
	{
		"구멍파기", 
		"몸통박치기",
		"울음소리",
		"나가기"
	};

	player = Player::GetInstance();
}

void CombatUI::ChangeState(CombatUIState newState)
{
	currentState = newState; 

	selectedIndex = 0; 
	selectedSkillIndex = 0;
}

#pragma region Update 
void CombatUI::UpdateCommand()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex);
	}
}

void CombatUI::UpdateSkillSelect()
{
	if (HandleKeyInput(selectedSkillIndex, tempSkills.size()))
	{
		// 싸움 로직 
		switch (selectedSkillIndex)
		{	// 할퀴기  
		case 0: Battle(); break;
			
		case 1: Battle(); break;
			// 울음 소리 
		case 2:Battle(); break;
			// 나가기 
		case 3:
			ChangeState(CombatUIState::Command);
			break;
		}
	}
}

void CombatUI::UpdateResult()
{
}

#pragma endregion 

#pragma region Drawing 

void CombatUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}

void CombatUI::DrawTitleRect()
{
	DrawRect(titleRect);

	SetCursorPos(titleRect.InnerX() + 42, titleRect.InnerY() + 1);
	PrintColorString(ColorType::DarkGray, "전투");
}

void CombatUI::DrawMenuRect()
{
	menuRect = GetCenteredRect(30, 8);
	menuRect.x += 30;
	menuRect.y += 11;

	DrawRect(menuRect);

	switch (currentState)
	{
	case CombatUIState::Command:

		for (int i = 0; i < menus.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
			if (i == selectedIndex)
			{
				cout << "  ▶" << "[" << menus[i] << "]";
			}
			else
			{
				cout << "    ";
				PrintColorString(ColorType::DarkGray, menus[i]);
			}
		}

		break;

	case CombatUIState::SkillSelect:

		for (int i = 0; i < tempSkills.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
			if (i == selectedSkillIndex)
			{
				cout << "  ▶" << "[" << tempSkills[i] << "]";
			}
			else
			{
				cout << "    ";
				PrintColorString(ColorType::DarkGray, tempSkills[i]);
			}
		}

		break;
	}
}

void CombatUI::DrawScriptRect()
{
	scriptRect = GetCenteredRect(60, 8);
	scriptRect.x = canvasRect.x;
	scriptRect.y += 11;

	DrawRect(scriptRect);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

	switch (currentState)
	{
	case CombatUIState::Command:
		cout << "병권이는 무엇을 할까?";
		break;

	case CombatUIState::SkillSelect:
		cout << "선택";
		break;

	case CombatUIState::Result:
		cout << "전투 종료";
		Delay(1);
		
		ChangeState(CombatUIState::Command);
		break;
	}
}

void CombatUI::DrawInfoRects()
{
	playerInfoRect = GetCenteredRect(30, 4);
	playerInfoRect.x = canvasRect.InnerX() + 1;
	playerInfoRect.y += 4;

	MonsterInfoRect = GetCenteredRect(30, 4);
	MonsterInfoRect.x = canvasRect.InnerX() + 58;
	MonsterInfoRect.y = titleRect.InnerY() + 4;

	DrawRect(playerInfoRect);
	DrawRect(MonsterInfoRect);

	SetCursorPos(playerInfoRect.InnerX() + 10, playerInfoRect.InnerY());

	if (player)
	{
		cout << player->stats.name << "( " << player->stats.currentHealth << " / " << player->stats.maxHealth << " )";

		SetCursorPos(playerInfoRect.InnerX() + 1, playerInfoRect.InnerY() + 1);
		float HPBarCount =
			(static_cast<float>(player->stats.currentHealth) /
				static_cast<float>(player->stats.maxHealth)) * 26.0f;
		PrintColorString(ColorType::RED, string(static_cast<size_t>(round(HPBarCount)), '='));
	}

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());

	if (monster)
	{
		cout << monster->stats.name << "( " << monster->stats.currentHealth << " / " << monster->stats.maxHealth << " )";

		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY() + 1);
		float HPBarCount =
			(static_cast<float>(monster->stats.currentHealth) /
				static_cast<float>(monster->stats.maxHealth)) * 26.0f;

		PrintColorString(ColorType::RED, string(static_cast<size_t>(round(HPBarCount)), '='));
	}
	else // test code 
	{
		cout << "괴물 A (50/100)";

		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY() + 1);
		float HPBarCount = (50.0 / 100) * 26;
		PrintColorString(ColorType::RED, string(round(HPBarCount), '='));
	}
}

void CombatUI::DrawMonster()
{
	if (monster == nullptr) return;

	const vector<string>& monsterImage = monster->GetImageVector();
	int startX = canvasRect.InnerX() + 35;
	int startY = canvasRect.InnerY() + 3;

	for (int i = 0; i < monsterImage.size(); ++i)
	{
		SetCursorPos(startX, startY + i);
		PrintColorString(ColorType::DarkYellow, monsterImage[i]);
	}
}

#pragma endregion 

#pragma region Combat 

void CombatUI::ExecutePlayerTurn()
{
	switch (selectedSkillIndex)
	{
	case 0:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 땅 속 깊이 들어갔다 튀어 오르며 공격했습니다.";
		Delay(1);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		cout << "!!!! "<<player->stats.attack << " DMG !!!!";
		Delay(1);
		ClearRect(scriptRect);

		break;
	case 1:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 몸으로 힘껏 들이 받았습니다.";
		Delay(1);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		cout << "!!!! " << player->stats.attack << " DMG !!!!";
		Delay(1);
		ClearRect(scriptRect);

		break;
	case 2:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 구슬프게 울부짖습니다!";
		Delay(1);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		cout << "!!!! " << player->stats.attack << " DMG !!!!";
		Delay(1);
		ClearRect(scriptRect);

		break;
	}
}

void CombatUI::ExecuteMonsterTurn()
{
	monster->AttackTarget(player);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << monster->GetMonsterName() << "이/가 " << player->stats.name << " 을/를 공격했습니다.";
	Delay(1);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << monster->stats.attack << " DMG";
	Delay(1);
	ClearRect(scriptRect);
}

void CombatUI::Battle()
{
	if (!player || !monster) return;

	// 플레이어 행동
	ExecutePlayerTurn();

	if (monster->stats.bIsDead)
	{
		GiveRewards();
		monster = make_shared<Monster>("Mon", player->GetLevel(), 0);
		//SpawnMonster();

		return;
	}

	// 몬스터 행동
	ExecuteMonsterTurn();

	if (player->stats.bIsDead)
	{
		DefeatEvent();
		return;
	}

}

void CombatUI::GiveRewards()
{
	int inExp = 50;
	int inGold = Random::Choice(20, 30);

	// 플레이어 경험치 증가
	int checkLevel = player->GetLevel();
	player->TakeExp(inExp);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "+" << inExp << " EXP";
	Delay(1);
	if (player->GetLevel() > checkLevel)
	{
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY()+1);
		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
		Delay(1);
	}

	// 인벤토리에 골드 추가 
	player->TakeGold(inGold);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
	cout << "+" << inGold << " Gold";
	Delay(1);

	// 인벤토리에 아이템 추가
	ItemTable itemTable;
	Item item;
	Item* inItem = &item;
	switch(Random::Choice(0,1))
	{
	case 0:
		item = itemTable.GetItem("붕대");
		break;
	case 1:
		item = itemTable.GetItem("아드레날린");
		break;
	}
	if (inItem)
	{
		player->GetInventory()->AddItem(inItem, 1);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 3);
		cout << inItem->GetItemInfo().name << "을/를 획득했습니다.";
		Delay(1);
	}
}

void CombatUI::DefeatEvent()
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 죽었습니다.";
	Delay(1);
	ClearRect(scriptRect);
}

void CombatUI::PrintLogTest()
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "";
}

void CombatUI::SpawnMonster(int level)
{ 
	string name;
	int artIndex = Random::Choice(0, 2);
	switch (artIndex)
	{
	case 0:
		name = "Weak Monster";
		break;

	case 1:
		name = "Normal Monster";
		break;

	case 2:
		name = "Strong Monster";
		break;

	}

	if (player->GetLevel() >= 10)
	{
		name = "Boss Monster";
		artIndex = 3;
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << name << "을/를 마주쳤습니다.";

	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	monster = make_shared<Monster>(name, player->GetLevel(), artIndex);
	
	if (!monster) return;

}

#pragma endregion  