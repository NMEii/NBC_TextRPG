#include "pch.h"
#include "CombatUI.h"
#include "Random.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ItemTable.h"
#include "Inventory.h"
#include "BossMonster.h"

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
	//몬스터가 공백이 많으니까
	DrawPlayer();

	DrawTitleRect();

	DrawScriptRect();

	DrawMenuRect();

	DrawInfoRects();

	DrawDefeatRect();
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

	case CombatUIState::Defeat:
		UpdateDefeat();
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
		if (player->GetLevel() < 10)
			SpawnMonster(player->GetLevel());
		else
			SpawnBossMonster();
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

		killCount++;

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
	if (monster == nullptr)
		GiveRewards();

	ChangeState(CombatUIState::SpawnMonster);
}

void CombatUI::UpdateDefeat()
{
	int defeat = 0;
	if (HandleKeyInput(defeat, 0))
	{
		if (OnRequest)
			OnRequest(UIRequest::ClearCombat);
	}
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

	case CombatUIState::Defeat:
		cout << "병권이는 눈앞이 깜깜해지기 시작했다...";
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
			player->gender ? ColorType::Blue : ColorType::Red,
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
		PrintColorString(ColorType::Red, string(static_cast<size_t>(round(HPBarCount)), '='));
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

		PrintColorString(ColorType::Red, string(static_cast<size_t>(round(HPBarCount)), '='));
	}

}

void CombatUI::DrawMonster()
{
	if (monster == nullptr) return;

	const vector<string>& monsterImage = monster->GetImageVector();
	int startX = canvasRect.InnerX() + 30;
	int startY = canvasRect.InnerY() + 3;

	for (int i = 0; i < monsterImage.size(); ++i)
	{
		SetCursorPos(startX, startY + i);
		PrintColorString(ColorType::DarkYellow, monsterImage[i]);
	}
}

void CombatUI::DrawDefeatRect()
{
	if (currentState != CombatUIState::Defeat) return;

	UIRect DefaultRect = GetCenteredRect(60, 12);
	DrawRect(DefaultRect);

	vector<string> defeatArt = {
	"######  ####### ####### #######    #    #######",
	"#     # #       #       #         # #      #   ",
	"#     # #       #       #        #   #     #   ",
	"#     # #####   #####   #####   #     #    #   ",
	"#     # #       #       #       #######    #   ",
	"#     # #       #       #       #     #    #   ",
	"#     # #       #       #       #     #    #   ",
	"######  ####### #       ####### #     #    #   ",

	};

	for (int i = 0; i < defeatArt.size(); i++)
	{

		SetCursorPos(DefaultRect.InnerX() + 5, DefaultRect.InnerY() + i);

		PrintColorString(ColorType::Red, defeatArt[i]);
	}
	SetCursorPos(DefaultRect.InnerX() + 22, DefaultRect.InnerY() + 9);
	PrintColorString(ColorType::White, "Exit to Enter");
}

void CombatUI::DrawPlayer()
{
	if (player == nullptr) return;

	const vector<string>& playerImage = player->GetCharacterImage();
	int startX = canvasRect.InnerX() + 7;
	int startY = canvasRect.InnerY() + 5;
	for (int i = 0; i < playerImage.size(); ++i)
	{
		SetCursorPos(startX, startY + i);
		PrintColorString(ColorType::DarkRed, playerImage[i]);
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
		PrintColorString(ColorType::Red, to_string(player->stats.attack) + " 의 데미지를 입혔습니다.");
		PrintPassiveMessage();
		ClearRect(scriptRect);

		break;
	case 1:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 몸으로 힘껏 들이 받았습니다.";
		Delay(0.6f);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		PrintColorString(ColorType::Red, to_string(player->stats.attack) + " 의 데미지를 입혔습니다.");
		PrintPassiveMessage();
		ClearRect(scriptRect);

		break;
	case 2:
		player->Attack(monster.get());
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << player->stats.name << "이/가 구슬프게 울부짖습니다!";
		Delay(0.6f);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 1);
		PrintColorString(ColorType::Red, to_string(player->stats.attack) + " 의 데미지를 입혔습니다.");
		PrintPassiveMessage();
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
	PrintColorString(ColorType::Red, to_string(monster->stats.attack) + " 의 데미지를 입었습니다");
	PrintPassiveMessage();
	ClearRect(scriptRect);
}

void CombatUI::GiveRewards()
{
	int exp = 50;
	int gold = Random::Choice(10, 20);
	double itemPercent = 0.3;

	// 플레이어 경험치 증가
	int checkLevel = player->GetLevel();
	player->IncreaseExp(exp);

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	PrintColorString(ColorType::Blue, "+" + to_string(exp) + " EXP");

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
	Item* item = itemTable.GetRandomItem();

	/* 필수 기능 - 아이템 획득 확률 30퍼 추가 */
	if (item != nullptr && Random::Success(itemPercent))
	{
		player->GetInventory()->AddItem(item, 1);
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
		cout << item->GetItemInfo().name << "을/를 획득했습니다.";
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
		color = ColorType::Red;
		break;

	}

	if (bIsFirstSpawn)
	{
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

		cout << "눈 앞에 떨어져 있는 " << player->GetWeaponName() << "을(를) 주웠습니다.\n";
		bIsFirstSpawn = false;

		Delay(2.f);
		ClearRect(scriptRect);
	}

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());

	PrintColorString(ColorType::White, "야생의 ");
	PrintColorString(color, name);
	PrintColorString(ColorType::White, "가 튀어나왔다.");

	Delay(0.6f);
	ClearRect(scriptRect);
	SetCursorPos(menuRect.InnerX() + 1, menuRect.InnerY());

	monster = make_unique<Monster>(name, player->GetLevel(), artIndex);

	if (!monster) return;

}

void CombatUI::SpawnBossMonster()
{
	monster = make_unique<BossMonster>();

	SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY());
	PrintColorString(ColorType::DarkRed, "굉장한 괴음과 함께 보스가 등장합니다.");
	Delay(1.5f);


	ChangeState(CombatUIState::Command);
}

void CombatUI::PrintPassiveMessage()
{
	Delay(0.2f);
	vector<string> messages = player->GetMessages();

	for (const string& msg : messages) {
		SetCursorPos(scriptRect.InnerX() + 2, scriptRect.InnerY() + 2);
		PrintColorString(ColorType::Yellow, msg);

	}
	Delay(1.f);
}

#pragma endregion  