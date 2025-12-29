#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	bIsRunning = true;

	Initizlize(); 

	while (bIsRunning)
	{
		Render(); 

		Update(); 
	}

}

void GameManager::Initizlize()
{
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

void GameManager::ShutDown()
{
	bIsRunning = false;
}

void GameManager::Delay(float Time)
{
	Sleep(Time * 1000); 
}

void GameManager::ClearConsole()
{
	system("cls");
}

void GameManager::BindUIEvents()
{
}

void GameManager::HandleUIRequest(UIRequest req)
{
}
