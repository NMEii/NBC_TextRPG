#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

//플레이어를 스마트포인터로 받기, 
CombatUI::CombatUI(shared_ptr<Player> player)
	:targetPlayer(player)
{
	menus =
	{
		"싸운다",
		"인벤토리",
		"상점",
		"나가기",
	};
	tempSkills =
	{
		"할퀴기",
		"몸통박치기",
		"울음소리",
		"나가기"
	};

}

CombatUI::CombatUI() {}
CombatUI::~CombatUI() {}

void CombatUI::StartCombat()
{
	if (!targetPlayer)return;

	SpawnMonster(targetPlayer.get());

	currentState = CombatUIState::Command;
	selectedIndex = 0;
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

		if (HandleKeyInput(selectedIndex, menus.size()))
		{
			OnSelect(selectedIndex);
		}

		break;

	case CombatUIState::SkillSelect:
		if (HandleKeyInput(selectedSkillIndex, tempSkills.size()))
		{
			// 싸움 로직 
			switch (selectedSkillIndex)
			{
			case 0:
				//이때를 위해 prcessTurn 함수를 만들었습니다만 스킬 종류에 따른 효과를 아직;
				// 할퀴기  

				break;

			case 1:
				// 몸통박치기  

				break;

			case 2:
				// 울음 소리 
				break;

			case 3:
				// 나가기 
				currentState = CombatUIState::Command;
				break;
			}

		}
		break;

	case CombatUIState::Result:

		break;


	}


}

void CombatUI::OnSelect(int choice)
{
	if (choice == 0) // 싸운다 
	{
		currentState = CombatUIState::SkillSelect;
	}

	if (choice == 1 && OnRequest) // 인벤토리 
	{
		OnRequest(UIRequest::OpenInventoryUI);
	}
	if (choice == 2 && OnRequest) // 상점 
	{
		OnRequest(UIRequest::OpenStoreUI);
	}
	if (choice == 3 && OnRequest) // 나가기 
	{
		OnRequest(UIRequest::OpenMainMenu);
	}

}

void CombatUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}


void CombatUI::DrawTitleRect()
{
	DrawRect(titleRect);

	SetCursorPos(titleRect.InnerX() + 42, titleRect.InnerY() + 1);
	cout << "전투";
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
				cout << "  ▶ " << "[" << menus[i] << "]";
			}

			else
			{
				cout << "    " << menus[i];
			}
		}

		break;

	case CombatUIState::SkillSelect:

		for (int i = 0; i < tempSkills.size(); i++)
		{
			SetCursorPos(menuRect.InnerX() + 5, menuRect.InnerY()+1 + i);
			if (i == selectedSkillIndex)
			{
				cout << "  ▶ " << "[" << tempSkills[i] << "]";
			}

			else
			{
				cout << "    " << tempSkills[i];
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
		cout << "무엇을 하지?";
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
	if (currentMonster == nullptr) return;

	string ImageStr = currentMonster->GetImageString();
	int startX = canvasRect.InnerX() + 35;
	int startY = canvasRect.InnerY() + 3;

	std::stringstream ss(ImageStr);
	std::string line;
	int lineCount = 0;

	while (std::getline(ss, line))
	{
		SetCursorPos(startX, startY + lineCount);
		std::cout << line;

		lineCount++;
	}
}

void CombatUI::PlayerAttack(Player* player, shared_ptr<Monster> monster)
{
	player->Attack(monster.get());
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 " << monster->GetMonsterName() << " 을/를 공격했습니다.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << player->stats.attack << " DMG";
}

void CombatUI::MonsterAttack(Player* player, shared_ptr<Monster> monster)
{
	monster->AttackTarget(player);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << monster->GetMonsterName() << "이/가 " << player->stats.name << "을/를 공격했습니다.";
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << monster->stats.attack << " DMG";
}


void CombatUI::Battle(Player* player)
{
	shared_ptr<Monster> monster = SpawnMonster(player);
	PlayerAttack(player, monster);
	MonsterAttack(player, monster);
	
}


void CombatUI::GetExp(Player* player)
{
	int inExp = 50;
	player->TakeExp(inExp);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "+" << inExp << " EXP";
	if (player->GetExp() >= 100)
	{
		player->SetExp(0);
		player->LevelUp();
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << "레벨 업! 현재 레벨: " << player->GetLevel();
	}
	
}

void CombatUI::GetGold(Player* player)
{
	int inGold = Random::Choice(10, 20);
	player->TakeGold(inGold);
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
	cout << "+" << inGold << " Gold";
}

void CombatUI::DropItem(Player* player)
{
	double percent = 0.3;
	if (Random::Success(percent))
	{
		Item* item = nullptr;
		player->TakeItem(item);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
		cout << "아이템" << item->GetItemInfo().name << "을/를 획득했습니다.";

	}
}

void CombatUI::VictoryEvent(Player* player)
{
	GetExp(player);
	GetGold(player);
	DropItem(player);
}
	

void CombatUI::DefeatEvent(Player* player)
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << player->stats.name << "이/가 죽었습니다.";
}

void CombatUI::PrintLogTest()
{
	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	cout << "";
}

shared_ptr<Monster> CombatUI::SpawnMonster(Player* player)
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
	/* 보스일때
	if (artIndex == 3)
	{
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		cout << "뭔가 느낌있는 말을 넣고싶어~~";
	}
	*/
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	return make_shared<Monster>(name, player->GetLevel(), artIndex);
}

//전투메뉴의 스킬인덱스를 매개변수로
void CombatUI::ProcessTurn(int skillIndex)
{
	if (!targetPlayer || !currentMonster) return;

	PlayerAttack(targetPlayer.get(), currentMonster);
	//죽었냐?! 체크
	if (currentMonster->stats.bIsDead)
	{
		VictoryEvent(targetPlayer.get());
		currentState = CombatUIState::Result;
		return;
	}

	//몬스터가 덤벼요
	MonsterAttack(targetPlayer.get(), currentMonster);

	//플레이어 죽었냐?!
	if (targetPlayer->stats.bIsDead)
	{
		DefeatEvent(targetPlayer.get());
		currentState = CombatUIState::Result;
	}
	else
	{
		currentState = CombatUIState::Command;
	}
}

void CombatUI::DrawInfoRects()
{
	playerInfoRect = GetCenteredRect(30, 4); 
	playerInfoRect.x = canvasRect.InnerX() + 58;
	playerInfoRect.y += 4; 

	MonsterInfoRect = GetCenteredRect(30, 4);
	MonsterInfoRect.x = canvasRect.InnerX() + 1;
	MonsterInfoRect.y = titleRect.InnerY() + 4;

	DrawRect(playerInfoRect);
	DrawRect(MonsterInfoRect);

	SetCursorPos(playerInfoRect.InnerX() + 10, playerInfoRect.InnerY());
	cout << "병권 (150 / 200)";

	SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());
	cout << "괴물A (100 / 100)";

}

