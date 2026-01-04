#include "pch.h"
#include "GameManager.h"
#include "BaseUI.h"
#include "MainMenuUI.h"
#include "CombatUI.h"
#include "InventoryUI.h"
#include "ItemShopUI.h"
#include "EndingCreditUI.h"
#include "Player.h"

using namespace std;


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	bIsRunning = true;

	// GM 초기화 
	Initialize(); 

	// 메인 루프 
	while (bIsRunning)
	{
		Render(); 

		Update(); 

		Delay(0.016f); // ~60 FPS
	}
}

void GameManager::Initialize()
{
	// 메인 메뉴 생성 
	mainMenuUI = make_unique<MainMenuUI>(); 
	SetCurrentUI(mainMenuUI.get());

	// 엔딩 크레딧 테스트 
	/*endingCreditUI = make_unique<EndingCreditUI>();
	SetCurrentUI(endingCreditUI.get());*/

	player = Player::GetInstance();
}

void GameManager::Update()
{
	// 현재 메뉴의 업데이트 호출 
	if(currentMenu)
		currentMenu->Update(); 
}


void GameManager::Render()
{
	// 현재 메뉴의 렌더 호출
	if (currentMenu)
		currentMenu->Render(); 
}

void GameManager::ShutDown()
{
	// 메인 루프 탈출 
	bIsRunning = false;
}

void GameManager::Delay(float Time)
{
	// Time [초]  만큼 딜레이 
	Sleep(static_cast<DWORD>(Time * 1000));
}

void GameManager::BindUIEvents()
{
	currentMenu->OnRequest = [this](UIRequest req) {GameManager::HandleUIRequest(req); };
}

void GameManager::HandleUIRequest(UIRequest req)
{
	switch (req)
	{
	case UIRequest::ExitGame:
	{   // 게임 종료 
		ShutDown();
		break;
	}
	case UIRequest::OpenMainMenu:
	{
		inventoryUI.reset();
		itemShopUI.reset();

		if (mainMenuUI == nullptr)
			mainMenuUI = make_unique<MainMenuUI>();

		SetCurrentUI(mainMenuUI.get());
		break;
	}
	case UIRequest::OpenCombatUI: // 배틀 돌입 
	{
		itemShopUI.reset();
		inventoryUI.reset();

		if (combatUI == nullptr)
			combatUI = make_unique<CombatUI>();

		SetCurrentUI(combatUI.get());
		break;
	}
	case UIRequest::OpenInventoryUI: // 인벤토리 열기 
	{
		if (inventoryUI == nullptr)
			inventoryUI = make_unique<InventoryUI>();

		SetCurrentUI(inventoryUI.get());
		break;
	}
	case UIRequest::OpenStoreUI: // 상점 열기 
	{
		mainMenuUI.reset();
		inventoryUI.reset();

		itemShopUI = make_unique<ItemShopUI>();
		SetCurrentUI(itemShopUI.get());
		break;
	}
	case UIRequest::None:
	{
		break;
	}
	case UIRequest::OPenEndingCreditUI:
	{
		if (endingCreditUI == nullptr)
			endingCreditUI = make_unique<EndingCreditUI>();

		SetCurrentUI(endingCreditUI.get());

		break;
	}

	}
}

void GameManager::SetCurrentUI(BaseUI* newUI)
{
	currentMenu = newUI; 

	if(currentMenu) 
		BindUIEvents();
}

void GameManager::ResetUI(unique_ptr<BaseUI>& ui)
{
	if (currentMenu == ui.get())
		currentMenu = nullptr;

	ui.reset();
}
