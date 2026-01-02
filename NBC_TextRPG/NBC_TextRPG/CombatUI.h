#pragma once
#include "BaseUI.h"

enum class CombatUIState
{
	Command,
	SkillSelect,
	Result,
};

class CombatUI : public BaseUI
{
public:

	CombatUI();

	~CombatUI();

	// 화면 그리기 
	virtual void Render() override;

	// 화면 업데이트 
	virtual void Update() override;

	// 메뉴 선택 처리 
	void OnSelect(int choice) override;

protected:

	void DrawCanvasRect();

	void DrawTitleRect();

	void DrawMenuRect();

	void DrawScriptRect();

	void DrawInfoRects()
	{
		playerInfoRect = GetCenteredRect(30, 4);
		playerInfoRect.x = canvasRect.InnerX() + 58;
		playerInfoRect.y += 4;

		MonsterInfoRect = GetCenteredRect(30, 4);
		MonsterInfoRect.x = canvasRect.InnerX() + 1;
		MonsterInfoRect.y = titleRect.InnerY() + 4;

		DrawRect(playerInfoRect);
		DrawRect(MonsterInfoRect);

		SetCursorPos(playerInfoRect.InnerX() + 10, playerInfoRect.InnerY());
		cout << "병권 (150 / 200)";

		SetCursorPos(MonsterInfoRect.InnerX(), MonsterInfoRect.InnerY());
		cout << "괴물A (100 / 100)";
	}

	void DrawMonster();

private:
	bool bShouldDrawMenu = true;

	vector<string> skills;
	int selectedSkillIndex = 0;

	UIRect scriptRect;
	UIRect menuRect;
	UIRect playerInfoRect;
	UIRect MonsterInfoRect;

	CombatUIState currentState = CombatUIState::Command;
};

