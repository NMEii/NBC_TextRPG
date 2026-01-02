#include "pch.h"
#include "GameManager.h"
#include "BaseUI.h"
#include "MainMenuUI.h"
#include "CombatUI.h"
#include "InventoryUI.h"
#include "ItemShopUI.h"
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
	Initizlize(); 

	// 메인 루프 
	while (bIsRunning)
	{
		Render(); 

		Update(); 
	}

}

void GameManager::Initizlize()
{
	// 메인 메뉴 생성 
	currentMenu = std::make_unique<MainMenuUI>();
	BindUIEvents();

	// player = make_shared<Player>("name");
}

void GameManager::Update()
{
	// 현재 메뉴의 업데이트 호출 
	currentMenu->Update(); 
}


void GameManager::Render()
{
	// 현재 메뉴의 렌더 호출 
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
	Sleep(Time * 1000); 
}

void GameManager::BindUIEvents()
{
	currentMenu->OnRequest = [this](UIRequest req) {GameManager::HandleUIRequest(req); };
}

void GameManager::HandleUIRequest(UIRequest req)
{
	switch (req)
	{
	case UIRequest::ExitGame: // 게임 종료 
		ShutDown();
		break; 

	case UIRequest::OpenMainMenu:
		currentMenu = make_unique<MainMenuUI>(); 
		BindUIEvents();
		break;

	case UIRequest::OpenCombatUI: // 배틀 돌입 

		if (player)
		{
			currentMenu = make_unique<CombatUI>(player);
			BindUIEvents();
		}
		// 지울거 
		else
		{
			currentMenu = make_unique<CombatUI>();
			BindUIEvents();
		}


		break; 

	case UIRequest::OpenInventoryUI: // 인벤토리 열기 

		if (player) // 인벤토리 조건 추가 
		{
			currentMenu = make_unique<InventoryUI>();
			BindUIEvents();
		}
		// 지울거
		else
		{
			currentMenu = make_unique<InventoryUI>();
			BindUIEvents();
		}
		
		break; 

	case UIRequest::OpenStoreUI: // 상점 열기 

		if (player) // 인벤토리 조건 추가 
		{
			currentMenu = make_unique<ItemShopUI>();
			BindUIEvents();
		}
		// 지울거 
		else
		{
			currentMenu = make_unique<ItemShopUI>();
			BindUIEvents();
		}

		break; 


	case UIRequest::None:

		break; 
	}
}
