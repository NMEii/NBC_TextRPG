#pragma once
#include "BaseUI.h"



enum class CombatUIState
{
	SpawnMonster, 
	Command,
	SkillSelect,
	Result,
	PlayerTurn, 
	MonsterTurn, 
	Defeat, 
};

class Player; 
class Monster;
class Item;

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

	void UpdateSpawnMonster();

	void UpdateCommand(); 

	void UpdateSkillSelect();

	void UpdatePlayerTurn();

	void UpdateMonsterTurn(); 

	void UpdateResult(); 

	void UpdateDefeat(); 

	//엔드스크립트
	void EndScriptShow();
	//오픈스크립트
	void OpenScriptRect();

private:
	//몬스터 소환
	
	void SpawnMonster(int level);
	void SpawnBossMonster();

	//전투

	void ExecutePlayerTurn();

	void ExecuteMonsterTurn();

	void GiveRewards(); 

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

	void DrawDefeatRect(); 

	void DrawPlayer();

private:
	bool bShouldDrawMenu = true;

	vector<string> tempSkills;
	int selectedSkillIndex = 0;

	UIRect scriptRect;
	UIRect menuRect;
	UIRect playerInfoRect;
	UIRect MonsterInfoRect;

	CombatUIState currentState = CombatUIState::SpawnMonster;

	Player* player; 
	unique_ptr<Monster> monster; 
	
	int killCount = 0; 

	//엔딩스크립트
	const vector<string> EndScript();
	const vector<string> OpenScript();
	// Todo 
	// 상점UI로 제한 추가 
};

