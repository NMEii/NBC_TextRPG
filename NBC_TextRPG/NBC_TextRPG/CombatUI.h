#pragma once
#include "BaseUI.h"

class Monster;
class Player;
class Item;

enum class CombatUIState
{
	Command, 
	SkillSelect, 
	Result,
};

class Player; 

class CombatUI : public BaseUI
{
public:

	CombatUI(shared_ptr<Player> player);

	CombatUI();

	~CombatUI();

	// 화면 그리기 
	virtual void Render() override;

	// 화면 업데이트 
	virtual void Update() override;

	// 메뉴 선택 처리 
	void OnSelect(int choice) override;

	//몬스터 소환
	shared_ptr<Monster> SpawnMonster(Player* player);

	//전투
	void PlayerAttack(Player* player, shared_ptr<Monster> monster);

	void MonsterAttack(Player* player, shared_ptr<Monster> monster);

	void Battle(Player* player);

	//보상
	void GetExp(Player* player);

	void GetGold(Player* player);

	void DropItem(Player* player);

	void VictoryEvnet(Player* player);

	
	//패배
	void DefeatEvnet(Player* player);
	
	void PrintLogTest();

	


protected:
	
	void DrawCanvasRect();

	void DrawTitleRect(); 

	void DrawMenuRect();

	void DrawScriptRect();

	void DrawInfoRects(); 

protected:

	void SpawnMonster(); 

private:
	bool bShouldDrawMenu = true; 
	
	vector<string> tempSkills; 
	int selectedSkillIndex = 0; 

	UIRect scriptRect; 
	UIRect menuRect; 
	UIRect playerInfoRect;
	UIRect MonsterInfoRect; 

	CombatUIState currentState = CombatUIState::Command;
};

