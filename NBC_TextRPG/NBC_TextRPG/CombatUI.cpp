#include "pch.h"
#include "CombatUI.h"

CombatUI::CombatUI()
{
	menus =
	{
		"싸운다",
		"인벤토리",
		"메인메뉴",
	};

}

CombatUI::~CombatUI()
{
}

void CombatUI::Render()
{ 
	ClearConsole();

	cout << "===============================\n";
	cout << "           전투\n";
	cout << "===============================\n";
	cout << "\n";
	for (int i = 0; i < menus.size(); i++)
	{
		cout << "\t";
		if (i == selectedIndex) cout << ">";
		else cout << " ";

		cout << menus[i] << "\n\n";
	}
	cout << "\n";
}

void CombatUI::Update()
{
	int input = _getch();
	if (input == 224 || input == 0)
		input = _getch();

	Key key = static_cast<Key>(input);

	switch (key)
	{
	case Key::Up:
		if (selectedIndex > 0)
			selectedIndex--;
		break;

	case Key::Down:
		if (selectedIndex < menus.size() - 1)
			selectedIndex++;
		break;

	case Key::Enter:
		OnSelect(selectedIndex);
		break;
	}
}

void CombatUI::OnSelect(int choice)
{
	if (choice == 0 && OnRequest)
	{
		// 전투 로직 
	}

	if (choice == 1 && OnRequest)
		OnRequest(UIRequest::OpenInventoryUI); 

	if (choice == 2 && OnRequest)
		OnRequest(UIRequest::OpenMainMenu);
}
