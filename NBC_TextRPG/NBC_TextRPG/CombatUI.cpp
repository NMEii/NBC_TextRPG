#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ItemTable.h"

using namespace std; 

CombatUI::CombatUI()
{
	InitUI(); 
}


CombatUI::~CombatUI()
{
}

void CombatUI::Render()
{
	ClearConsole();

	DrawMonster();

	DrawCanvasRect();

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
	SpawnMonster(player->GetLevel());
}

void CombatUI::ChangeState(CombatUIState newState)
{
	currentState = newState; 

	selectedIndex = 0; 
	selectedSkillIndex = 0;
}

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
		case 0: break;
			// 몸통박치기  
		case 1: break;
			// 울음 소리 
		case 2: break;
			// 나가기 
		case 3: ChangeState(CombatUIState::Command); break;
		}
	}
}

void CombatUI::UpdateResult()
{
}

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
	}
}

#pragma endregion 

void CombatUI::ExecutePlayerTurn()
{
	player->Attack(monster.get());
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 " << monster->GetMonsterName() << " 을/를 공격했습니다.";
	Delay(1);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << player->stats.attack << " DMG";
	Delay(1);
	ClearRect(scriptRect);
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

void CombatUI::Battle(int inSkillIndex)
{
	if (!monster)
	{
		monster = make_shared<Monster>("Mon", 1,0);
	}
	// 싸움 로직 
	switch (inSkillIndex)
	{
	case 0:
		ExecutePlayerTurn();
		ExecuteMonsterTurn();
		if (player->stats.currentHealth <= 0 || monster->stats.currentHealth <= 0)
		{
			currentState = CombatUIState::Result;
		}

		break;

	case 1:
		ExecutePlayerTurn();
		ExecuteMonsterTurn();

		if (player->stats.currentHealth <= 0 || monster->stats.currentHealth <= 0)
		{
			currentState = CombatUIState::Result;
		}
		break;

	case 2:
		ExecutePlayerTurn();
		ExecuteMonsterTurn();
		if (player->stats.currentHealth <= 0 || monster->stats.currentHealth <= 0)
		{
			
			CombatUIState::Result;
		}
		break;

	case 3:
		// 나가기
		currentState = CombatUIState::Command;
		break;
	}

}

void CombatUI::GiveRewards()
{
	// 플레이어 경험치 증가

	// 인벤토리에 아이템 추가 

	// 인벤토리에 골드 추가 

}

void CombatUI::DefeatEvnet(Player* player)
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 죽었습니다.";
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
	cout << "이제 일반 몬스터는 상대도 안된다!";

	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	monster = make_shared<Monster>(name, player->GetLevel(), artIndex);
	
	if (!monster) return;

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
		float HPBarCount = (player->stats.currentHealth / player->stats.maxHealth) * 26;
		PrintColorString(ColorType::RED, string(round(HPBarCount), '='));
	}

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());

	if (monster)
	{
		cout << monster->stats.name << "( " << monster->stats.currentHealth << " / " << monster->stats.maxHealth << " )";

		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY() + 1);
		float HPBarCount = (monster->stats.currentHealth / monster->stats.maxHealth) * 26;
		PrintColorString(ColorType::RED, string(round(HPBarCount), '='));
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
