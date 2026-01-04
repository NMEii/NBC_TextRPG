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
	Battle,
};

class Player; 

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
	virtual void InitUI() override; 

protected:

	void ChangeState(CombatUIState newState); 

protected:

	void UpdateCommand(); 

	void UpdateSkillSelect();

	void UpdateResult(); 

	void UpdateBattle();

private:
	//몬스터 소환
	
	void SpawnMonster(int level);

	//전투

	void ExecutePlayerTurn();

	void ExecuteMonsterTurn();

	void StartBattle(int monsterLevel);

	void Battle();

	void EndBattle();

	// 여기 
	// 보상
	void GiveRewards(); 

	void DropItem();

	
	//패배
	void DefeatEvent();
	
	void PrintLogTest();

protected:

	void DrawCanvasRect();

	void DrawTitleRect();

	void DrawMenuRect();

	void DrawScriptRect();

	void DrawInfoRects();

	void DrawMonster();

private:
	bool bShouldDrawMenu = true;

	vector<string> tempSkills;
	int selectedSkillIndex = 0;

	UIRect scriptRect;
	UIRect menuRect;
	UIRect playerInfoRect;
	UIRect MonsterInfoRect;

	CombatUIState currentState = CombatUIState::Command;

	Player* player; 
	shared_ptr<Monster> monster; 
	bool bInBattle = false;
};

