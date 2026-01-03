// Player.h
#pragma once
#include "Character.h"
#include "Buff.h"
#include "Weapon.h"
#include <map>

class Inventory;
class Item;

class Player : public Character
{
private:
	static Player* instance; // 유일한 플레이어 객체를 가리키는 정적 포인터
	int level;				 // 레벨
	int exp;				 // 경험치

	// map<string, int> killLog;
	vector<BuffInfo> buffs;
	WeaponType myWeapon;
	Inventory* inventory;

	Player(string name, WeaponType weapon);

public:
	// 복사 생성자 및 대입 연산자 삭제 (싱글톤 구현)
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* GetInstance(); // 싱글톤 인스턴스 반환 함수

	int GetLevel() const; // 레벨 출력 함수
	int GetExp() const;	  // 경험치 출력 함수
	int GetGold() const;  // 골드 출력 함수

	void LevelUp(); // 레벨업 함수

	void AquireItem(Item* item); // 아이템 획득 함수 to EarnReward
	void IncreaseEXP();			 // 경험치 증가 함수 to EarnReward
	void AquireGold();			 // 골드 증가 함수 to EarnReward

	// void SetKillLog(const string &monsterName); // 킬 로그 설정 함수
	// void GetKillLog() const;					// 킬 로그 출력 함수

	void Attack(Character* monster);				// 공격 함수
	void GetDamage(int amount, Character* monster); // 피격 함수

	void AddBuff(BuffInfo inBuff); // 버프 추가 함수
	void ResetBuff();			   // 버프한 스텟 초기화 함수

	// void UseItem(Item* item);	// 아이템 사용 함수
};