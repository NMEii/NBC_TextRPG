#include "pch.h"
#include "MainMenuUI.h"
#include "Player.h"

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
	if (choice == 0 && OnRequest)
	{
		if(bFirstEnter) DrawCharacterUI();
		OnRequest(UIRequest::OpenCombatUI);
	}


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

	bFirstEnter = true; 
}

void MainMenuUI::DrawCharacterUI()
{
	UIRect inputRect = GetCenteredRect(60, 11);
	DrawRect(inputRect);

	SetCursorPos(inputRect.InnerX() + 11, inputRect.InnerY() + 4);
	cout << "이름을 입력해 주세요 : ";
	char buffer[256];
	cin.getline(buffer, 256);
	ClearRect(inputRect);

	SetCursorPos(inputRect.InnerX() + 4, inputRect.InnerY() + 4);
	PrintColorString(ColorType::Green, buffer);
	cout << "을(를) 병권몬스터 세계의 이름으로 변경 중...";

	Delay(4.0f);
	ClearRect(inputRect);

	SetCursorPos(inputRect.InnerX() + 11, inputRect.InnerY() + 4);
	cout << "이름이 ";
	PrintColorString(ColorType::Green, "\"병권\"");
	cout << " (으)로 변경되었습니다!";
	Delay(2.0f);
	ClearRect(inputRect);
	bFirstEnter = false;
}

void MainMenuUI::DrawCanvasRect()
{
	DrawRect(canvasRect);
}

void MainMenuUI::DrawTitleRect()
{
	DrawRect(titleRect);

	SetCursorPos(titleRect.InnerX() + 40, titleRect.InnerY() + 1);
	PrintColorString(ColorType::DarkRed, "병권몬스터");
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
			cout << "    ";
			PrintColorString(ColorType::DarkGray, menus[i]);
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
		"      ,'\"    _       _  \"`.",
		"     /.__, ._  -=- _\"`   Y",
		"    (.____.-.`       \"\"` j",
		"     VvvvvvV`.Y,.    _.,-'        ,      ,      ,",
		"        Y    ||,   '\"\\         ,/     ,/     ./",
		"        |    ,'  ,      `-..,'_,'/___,'/   ,'/    ,",
		"   ..  ,;,,',-'\"\\,'  ,  .      '      ' \"\"' '--,/    .. ..",
		" ,'. `.`---'      `, /  , Y -=-    ,'    ,    ,. .`-..||_|| ..",
		"ff\\\\`. `._         /f ,'j j , ,' ,    , f ,  \\=\\ Y   || ||`||_..",
		"l` \\` `.`.\"`-..,-' j  /./ /, , / , / /l \\   \\=\\l   || `' || ||..",
		" `  `    `-._ `-.,-/ ,' /`\"/-/-/-/-\"'''\"`.`.  `'.\\--`'--..`'_`' |",
		"            \"`-_,',  ,'  f    ,    /       `._    ``._      ,  `-.`'",
		"          ,-3\"'' _.,-'    l_,-'_,,'           \"`-._ . \"`. /|     `",
		"        ,',.,-'\"           \\=) ,`-.          ,    `-'._`.V |     \\",
		"        |f\\\\                `._ )-.\"`.      /|         `.| |      ",
		"        l` \\`                 \"`._   \"`--' j            j' j      ",
		"         `  `                     \"`,-  ,'/          ,-'\"  /",
		"                                 ,'\",__,-'          /,, ,-'",
		"                                 Vvv'               VVv'"
	};

	for (int i = 0; i < monsterArt.size(); i++)
	{
		SetCursorPos(canvasRect.InnerX() + 20, canvasRect.InnerY() + 5 + i);
		PrintColorString(ColorType::Yellow, monsterArt[i]);
	}

}

