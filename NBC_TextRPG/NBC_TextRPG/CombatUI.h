#pragma once
#include "BaseUI.h"

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

private:
	bool bShouldDrawMenu = true; 
	
	vector<string> skills; 
	int selectedSkillIndex = 0; 

	UIRect scriptRect; 
	UIRect menuRect; 
};

