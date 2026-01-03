#include "pch.h"
#include "MainMenuUI.h"

using namespace std; 

MainMenuUI::MainMenuUI()
{
	InitUI(); 
	
}

MainMenuUI::~MainMenuUI()
{
}

void MainMenuUI::Render()
{
	ClearConsole();

	DrawCanvasRect();

	DrawTitleRect(); 

	DrawMonster();
	
	DrawMenuRect();
	
	DrawkeyRect();

	SetCursorPos(0, KeyRect.y + 5);
}

void MainMenuUI::Update()
{
	if (HandleKeyInput(selectedIndex, menus.size()))
	{
		OnSelect(selectedIndex);
	}
}

void MainMenuUI::OnSelect(int choice)
{
	// 예시 
	if (choice == 0 && OnRequest)
		OnRequest(UIRequest::OpenCombatUI);
	
	if (choice == 1 && OnRequest)
		OnRequest(UIRequest::ExitGame);
}

void MainMenuUI::InitUI()
{
	menus =
	{
		"게임 시작",
		"게임 종료"
	};
}


void MainMenuUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}

void MainMenuUI::DrawTitleRect()
{
	DrawRect(titleRect);

	SetCursorPos(titleRect.InnerX() + 40, titleRect.InnerY() + 1);
	PrintColorString(ColorType::DarkPurple, "병권몬스터");
}


void MainMenuUI::DrawMenuRect()
{

	menuRect = GetCenteredRect(60, 8);

	for (int i = 0; i < menus.size(); i++)
	{
		SetCursorPos(menuRect.x + 22, menuRect.y + 9 + i * 2);
		if (i == selectedIndex)
		{
			cout << "  ▶ " << "[" << menus[i] << "]";
		}

		else
		{
			cout << "    " << menus[i];
		}
	}

}


void MainMenuUI::DrawkeyRect()
{
	KeyRect = GetCenteredRect(90, 4);
	KeyRect.y += 13;

	DrawRect(KeyRect);

	SetCursorPos(KeyRect.x + 35, KeyRect.y + 1);
	cout << "↑↓ 이동 / ENTER 선택";
}

void MainMenuUI::DrawMonster()
{
	vector<string> monsterArt =
	{
		"         __.,,------.._",
		"      ,'\"   _      _   \"`.",
		"     /.__, ._  -=- _\"`    Y",
		"    (.____.-.`      \"\"`   j",
		"     VvvvvvV`.Y,.    _.,-'       ,     ,     ,",
		"        Y    ||,   '\"\\         ,/    ,/    ./",
		"        |   ,'  ,     `-..,'_,'/___,'/   ,'/   ,",
		"   ..  ,;,,',-'\"\\,'  ,  .     '     ' \"\"' '--,/    ..",
		" ,'. `.`---'     `, /  , Y -=-    ,'   ,   ,. .`-..||",
		"ff\\\\`. `._        /f ,'j j , ,' ,   , f ,  \\=\\ Y   ||",
		"l` \\` `.`.\"`-..,-' j  /./ /, , / , / /l \\   \\=\\l   ||",
		" `  `   `-._ `-.,-/ ,' /`\"/-/-/-/-\"'''\"`.`.  `'.\\--`'",
		"            \"`-_,',  ,'  f    ,   /      `._    ``._ ",
		"          ,-'\"'' _.,-'    l_,-'_,,'          \"`-._ . \"",
		"        ,',.,-'\"          \\=) ,`-.         ,    `-'._",
		"        |f\\\\               `._ )-.\"`.     /|         ",
		"        l` \\`                 \"`._   \"`--' j         ",
		"         `  `                     \"`,-  ,'/       ,-'",
		"                                 ,'\" ,__,-'       /,, ",
		"                                 Vvv'            VVv'"
	};

	for (int i = 0; i < monsterArt.size(); i++)
	{
		SetCursorPos(canvasRect.InnerX() + 20, canvasRect.InnerY() + 5 +i);
		cout << monsterArt[i];
	}

}
 
