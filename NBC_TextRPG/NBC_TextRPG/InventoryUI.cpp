#include "pch.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	menus = {

		"나가기"
	};
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Render()
{

	ClearConsole();

	cout << "===============================\n";
	cout << "           인벤토리\n";
	cout << "===============================\n";
	cout << "\n";
	// 아이템 출력 

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

void InventoryUI::Update()
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

void InventoryUI::OnSelect(int choice)
{
	if (choice == 0 && OnRequest)
		OnRequest(UIRequest::OpenCombatUI);

}
