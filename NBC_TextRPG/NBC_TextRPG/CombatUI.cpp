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
	case CombatUIState::SpawnMonster:

		UpdateSpawnMonster(); 
		break; 

	case CombatUIState::Command:

		UpdateCommand();
		break;
	case CombatUIState::SkillSelect:

		UpdateSkillSelect();
		break;

	case CombatUIState::PlayerTurn:

		UpdatePlayerTurn();
		break;

	case CombatUIState::MonsterTurn:

		UpdateMonsterTurn(); 
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
	case 0:
		// 싸운다 
		ChangeState(CombatUIState::SkillSelect);
		break;
	
	case 1: 
		// 인벤토리
		if (OnRequest)
			OnRequest(UIRequest::OpenInventoryUI);

		break;
		
	case 2: 
		// 상점 
		if (OnRequest)
			OnRequest(UIRequest::OpenStoreUI);

		break;
		
	case 3: 
		// 나가기 
		if (OnRequest)
			OnRequest(UIRequest::OpenMainMenu);
		
		break;
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
void CombatUI::UpdateSpawnMonster()
{
	if (monster == nullptr)
	{
		SpawnMonster(player->GetLevel());
	}

	ChangeState(CombatUIState::Command);
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
		case 0: 
			ChangeState(CombatUIState::PlayerTurn); 
			break; 
		case 1: 
			ChangeState(CombatUIState::PlayerTurn);
			break;
			// 울음 소리 
		case 2:
			ChangeState(CombatUIState::PlayerTurn);
			break;
			// 나가기 
		case 3:
			ChangeState(CombatUIState::Command);
			break;
		}
	}
}

void CombatUI::UpdatePlayerTurn()
{
	if (player == nullptr || monster == nullptr) return;

	ExecutePlayerTurn();

	if (monster->stats.bIsDead)
	{
		if (monster->stats.name == "Boss Monster")
		{
			if (OnRequest)
				OnRequest(UIRequest::OpenEndingCreditUI);

			return;
		}

		monster = nullptr;

		player->ResetBuff();

		ChangeState(CombatUIState::Result);
		return;
	}

	ChangeState(CombatUIState::MonsterTurn);
}

void CombatUI::UpdateMonsterTurn()
{
	if (player == nullptr || monster == nullptr) return;

	ExecuteMonsterTurn();

	if (player->stats.bIsDead)
	{

		ChangeState(CombatUIState::Result);
		return;
	}

	ChangeState(CombatUIState::Result);
}

void CombatUI::UpdateResult()
{
	if(monster == nullptr)
		GiveRewards(); 

	ChangeState(CombatUIState::SpawnMonster);
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
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY() + 1 + i);
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
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY() + 1 + i);
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

	if (player)
	{
		SetCursorPos(playerInfoRect.InnerX() + 1, playerInfoRect.InnerY());
		PrintColorString(ColorType::White, "Lv. " + to_string(player->GetLevel()));

		SetCursorPos(playerInfoRect.InnerX() + 7, playerInfoRect.InnerY());

		PrintColorString(ColorType::DarkYellow, player->stats.name);

		PrintColorString(
			player->gender? ColorType::Blue : ColorType::red, 
			player->gender ? " ♂" : " ♀"
		);
		
		SetCursorPos(playerInfoRect.InnerX() + 14, playerInfoRect.InnerY());
		string hpInfo = " ( " + to_string(player->stats.currentHealth) + " /" + to_string(player->stats.maxHealth) +
			" )";
		PrintColorString(ColorType::White, hpInfo);


		SetCursorPos(playerInfoRect.InnerX() + 1, playerInfoRect.InnerY() + 1);
		float HPBarCount =
			(static_cast<float>(player->stats.currentHealth) /
				static_cast<float>(player->stats.maxHealth)) * 26.0f;
		PrintColorString(ColorType::red, string(static_cast<size_t>(round(HPBarCount)), '='));
	}

	

	if (monster)
	{
		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());

		string name = monster->stats.name;
		ColorType color = ColorType::White;

		if (name == "Strong Monster") color = ColorType::DarkRed;
		else if (name == "Normal Monster") color = ColorType::DarkGreen;
		else if (name == "Weak Monster") color = ColorType::DarkYellow;
		else if (name == "Boss Monster") color = ColorType::DarkGreen;

		PrintColorString(color, monster->stats.name);

		cout << " ( " << monster->stats.currentHealth << " / " << monster->stats.maxHealth << " )";




		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY() + 1);
		float HPBarCount =
			(static_cast<float>(monster->stats.currentHealth) /
				static_cast<float>(monster->stats.maxHealth)) * 26.0f;

		PrintColorString(ColorType::red, string(static_cast<size_t>(round(HPBarCount)), '='));
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
		Delay(0.6f);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		PrintColorString(ColorType::red, "!!!! " + to_string(player->stats.attack) + " DMG !!!!");
		Delay(0.6f);
		ClearRect(scriptRect);

		break;
	case 1:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 몸으로 힘껏 들이 받았습니다.";
		Delay(0.6f);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		PrintColorString(ColorType::red, "!!!! " + to_string(player->stats.attack) + " DMG !!!!");
		Delay(0.6f);
		ClearRect(scriptRect);

		break;
	case 2:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 구슬프게 울부짖습니다!";
		Delay(0.6f);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		PrintColorString(ColorType::red, "!!!! " + to_string(player->stats.attack) + " DMG !!!!");
		Delay(0.6f);
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



void CombatUI::GiveRewards()
{
	int exp = 50;
	int gold = Random::Choice(20, 30);

	// 플레이어 경험치 증가
	int checkLevel = player->GetLevel();
	player->IncreaseExp(exp);

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	PrintColorString(ColorType::Blue, "+" + to_string(exp) +" EXP");

	Delay(0.5f);
	ClearRect(scriptRect); 
	if (player->GetLevel() > checkLevel)
	{
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
		Delay(0.5f);
	}

	ClearRect(scriptRect);
	// 인벤토리에 골드 추가 
	player->GetInventory()->gold += gold;
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	PrintColorString(ColorType::Yellow, "+" + to_string(gold) + " Gold");


	Delay(0.5f);
	ClearRect(scriptRect);

	// 인벤토리에 아이템 추가
	ItemTable itemTable;
	
	Item* item = new Item();
	switch(Random::Choice(0,1))
	{
	case 0:
		*item = itemTable.GetItem("붕대");
		break;
	case 1:
		*item = itemTable.GetItem("아드레날린");
		break;
	}

	if (item != nullptr)
	{
		player->GetInventory()->AddItem(item, 1);
		SetCursorPos(scriptRect.InnerX()+2, scriptRect.InnerY());
		cout << item->GetItemInfo().name << "을/를 획득했습니다.";
		Delay(1);
	}
	ClearRect(scriptRect);
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
	ColorType color;

	int artIndex = Random::Choice(0, 2);
	switch (artIndex)
	{
	case 0:
		name = "Weak Monster";
		color = ColorType::DarkYellow;
		break;

	case 1:
		name = "Normal Monster";
		color = ColorType::DarkGreen;
		break;

	case 2:
		name = "Strong Monster";
		color = ColorType::DarkRed;
		break;

	}

	if (player->GetLevel() >= 10)
	{
		name = "Boss Monster";
		artIndex = 3;
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

	PrintColorString(color, name);
	cout << "을/를 마주쳤습니다.";
	Delay(0.6f);
	ClearRect(scriptRect);
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	monster = make_unique<Monster>(name, player->GetLevel(), artIndex);
	
	if (!monster) return;

}

#pragma endregion  