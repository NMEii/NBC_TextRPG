#include "pch.h"
#include "MainMenuUI.h"

using namespace std; 

void MainMenuUI::Render()
{
	ClearConsole();

	cout << "===============================\n";
	cout << "           병권테일\n";
	cout << "===============================\n";
	cout << "\n";
	cout << " 게임시작\n";
	cout << " 게임종료\n"; 
	cout << "\n"; 
}

void MainMenuUI::Update()
{
	Move(pos); 
	cout << ">"; 

	HandleKeyInput(pos, Range);
}

void MainMenuUI::OnSelect(int choice)
{
	// 예시 
	if (choice == 1 && OnRequest)
		OnRequest(UIRequest::None);
	

}


