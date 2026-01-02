//Player.h
#pragma once
#include "Character.h"
#include "Buff.h"
#include "Weapon.h"
#include <map>

class Player : public Character
{
private:
	int level;		// 레벨
	int exp;		// 경험치
	int gold;		// 골드

	map<string, int> killLog;
	vector<BuffInfo> buffs;
	WeaponType myWeapon;

public:
	Player(string name);

	int GetLevel() const;	// 레벨 출력 함수
	int GetExp() const;		// 경험치 출력 함수
	int GetGold() const;	// 골드 출력 함수

	void LevelUp();		// 레벨업 함수
	void EarnReward();	// 보상 획득 함수

	void TakeItem(double percent);	// 아이템 획득 함수 to EarnReward
	void TakeExp(int inExp);		// 경험치 증가 함수 to EarnReward
	void TakeGold(int inGold);		// 골드 증가 함수 to EarnReward

	void SetKillLog(const string& monsterName); // 킬 로그 설정 함수
	void GetKillLog() const;					// 킬 로그 출력 함수

	void Attack(Character* monster);				// 공격 함수
	void GetDamage(int amount, Character* monster);	// 피격 함수

	void AddBuff(BuffInfo inBuff);	// 버프 추가 함수
	void ResetBuff();				// 버프한 스텟 초기화 함수

	// void UseItem(Item* item);	// 아이템 사용 함수
};