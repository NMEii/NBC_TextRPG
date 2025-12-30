#include "pch.h"
#include "GameManager.h"
#include "BaseUI.h"
#include "MainMenuUI.h"


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
}
