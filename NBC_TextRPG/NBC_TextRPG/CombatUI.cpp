#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ItemTable.h"

CombatUI::CombatUI()
{
	InitUI(); 
}


CombatUI::~CombatUI()
{
}

// 화면 그리기 
inline void CombatUI::Render()
{
	ClearConsole();
	// 캔버스 그리기 
	DrawCanvasRect();
	// 제목 그리기 
	DrawTitleRect();
	//몬스터 그리기 완전임시!!!
	DrawMonster();
	// 스크립트 그리기 
	DrawScriptRect();
	// 메뉴 그리기 
	DrawMenuRect();

	// 캐릭터 / 적 정보 그리기 
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
		currentState = CombatUIState::Command;

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
		monster = make_shared<Monster>("Mon", 1);
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
			currentState = CombatUIState::Result;
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
}


//void CombatUI::GetExp(Player* player)
//{
//	int inExp = 50;
//	player->TakeExp(inExp);
//	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
//	cout << "+" << inExp << " EXP";
//	if (player->GetExp() >= 100)
//	{
//		player->SetExp(0);
//		player->LevelUp();
//		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
//		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
//	}
//	
//}

//void CombatUI::GetGold(Player* player)
//{
//	int inGold = Random::Choice(10, 20);
//	player->TakeGold(inGold);
//	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
//	cout << "+" << inGold << " Gold";
//}

/*void CombatUI::DropItem()
{
	
	double percent = 0.3;
	if (Random::Success(percent))
	{
		Item* item = nullptr;
		switch (Random::Choice(1, 2))
		{
		case 1:
			item = ItemTable::GetItem("붕대");
			break;

		case 2:
			item = ItemTable::GetItem("아드레날린");
			break;

		}
		player->TakeItem(item);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
		cout << "아이템" << item->GetItemInfo().name << "을/를 획득했습니다.";

	}
}*/

//void CombatUI::VictoryEvnet(Player* player)
//{
//	GetExp(player);
//	GetGold(player);
//	DropItem(player);
//}
	

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
{ /*
	string name;
	switch (Random::Choice(1, 3))
	{
	case CombatUIState::Command:
		cout << "병권이는 무엇을 할까?";
		break;

	case CombatUIState::SkillSelect:
		cout << "선택";
		break;

	case CombatUIState::Result:
		// 싸움 스크립트... 

		break;
	}



}

void CombatUI::DrawMonster()
{
	if (monster == nullptr) return;

	const std::vector<std::string>& lines = monster->GetImageVector();
	int startX = canvasRect.InnerX() + 35;
	int startY = canvasRect.InnerY() + 3;

	for (int i = 0; i < lines.size(); ++i)
	{
		SetCursorPos(startX, startY + i);
		std::cout << lines[i];
	}
}
void CombatUI::ExecutePlayerTurn()
{
	player->Attack(monster.get());
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 " << monster->GetMonsterName() << " 을/를 공격했습니다.";

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << player->stats.attack << " DMG";
}



void CombatUI::ExecuteMonsterTurn()
{
	monster->AttackTarget(player);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << monster->GetMonsterName() << "이/가 " << player->stats.name << "을/를 공격했습니다.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << monster->stats.attack << " DMG";
}

void CombatUI::Battle()
{
	if (!monster)
	{
		SpawnMonster(player->GetLevel()); 
	}

	
	ExecutePlayerTurn();
	ExecuteMonsterTurn(); 
	
}

void CombatUI::GiveRewards()
{
}


//void CombatUI::GetExp(Player* player)
//{
//	int inExp = 50;
//	player->TakeExp(inExp);
//	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
//	cout << "+" << inExp << " EXP";
//	if (player->GetExp() >= 100)
//	{
//		player->SetExp(0);
//		player->LevelUp();
//		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
//		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
//	}
//	
//}

//void CombatUI::GetGold(Player* player)
//{
//	int inGold = Random::Choice(10, 20);
//	player->TakeGold(inGold);
//	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
//	cout << "+" << inGold << " Gold";
//}

//void CombatUI::DropItem(Player* player)
//{
//	
//
//	double percent = 0.3;
//	if (Random::Success(percent))
//	{
//		Item* item = nullptr;
//		player->TakeItem(item);
//		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
//		cout << "아이템" << item->GetItemInfo().name << "을/를 획득했습니다.";
//
//	}
//}

//void CombatUI::VictoryEvnet(Player* player)
//{
//	GetExp(player);
//	GetGold(player);
//	DropItem(player);
//}
	case 1:
		name = "Weak Monster";
		break;

	case 2:
		name = "Normal Monster";
		break;

	case 3:
		name = "Strong Monster";
		break;

	}

	if (player->GetLevel() >= 10)
	{
		name = "Boss Monster";
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << name << "을/를 마주쳤습니다.";
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	return make_shared<Monster>(name, player->GetLevel());*/


	// 몬스터가 이미 있으면 스폰할 필요 x 
	if (!monster) return; 


	// 레벨 10 이면 보스 몬스터 

	// 나머지는 플레이어 레벨의 0.8 ~ 1.3 범위 내의 몬스터 스폰 해주시면 될듯?  
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
		PrintColorString(ColorType::RED,string(round(HPBarCount), '='));
	}

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());

	if (monster)
	{
		cout << monster->stats.name << "( " << monster->stats.currentHealth << " / " << monster->stats.maxHealth << " )"; 
		
		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY()+1);
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
{ /*
	int artIndex = RandomChoice(0,2);
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
		artIndex =3;
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << name << "을/를 마주쳤습니다.";
	보스일때
	if (artIndex == 3)
	{
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		cout << "뭔가 느낌있는 말을 넣고싶어~~";
	}
	
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	return make_shared<Monster>(name, player->GetLevel(), artIndex);
	*/


	// 몬스터가 이미 있으면 스폰할 필요 x 
	if (!monster) return; 


	// 레벨 10 이면 보스 몬스터 

	// 나머지는 플레이어 레벨의 0.8 ~ 1.3 범위 내의 몬스터 스폰 해주시면 될듯?  
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
		PrintColorString(ColorType::RED,string(round(HPBarCount), '='));
	}

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());

	if (monster)
	{
		cout << monster->stats.name << "( " << monster->stats.currentHealth << " / " << monster->stats.maxHealth << " )"; 
		
		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY()+1);
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

