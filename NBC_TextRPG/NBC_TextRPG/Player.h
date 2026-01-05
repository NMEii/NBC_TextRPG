//Player.h
#pragma once
#include "Character.h"
#include "Weapon.h"

class Inventory;
class Item;
class Buff;

struct BuffInfo;

class Player : public Character
{
private:
	static Player* instance;// 유일한 플레이어 객체를 가리키는 정적 포인터
	Inventory* inventory;
	// map<string, int> killLog;
	vector<BuffInfo> buffs;
	WeaponType myWeaponType;
	unique_ptr<Weapon> myWeapon;
	int level;				// 레벨
	int exp;				// 경험치

	Player(string name, WeaponType weapon);

public:
	bool gender = true; 
	// 복사 생성자 및 대입 연산자 삭제 (싱글톤 구현)
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* GetInstance(); // 싱글톤 인스턴스 반환 함수

	Weapon* GetWeapon() const { return myWeapon.get(); } // 무기 타입 반환 함수

	int GetLevel() const { return level; }	// 레벨 출력 함수
	int GetExp() const { return exp; }		// 경험치 출력 함수

	//void SetKillLog(const string& monsterName);	// 킬 로그 설정 함수
	//void GetKillLog() const;						// 킬 로그 출력 함수

	void LevelUp();		// 레벨업 함수

	Inventory* GetInventory() { return inventory; }

	void AquireItem(Item* item);	// 아이템 획득 함수
	void IncreaseExp(int inExp);	// 경험치 증가 함수

	void Attack(Character* target);	// 공격 함수
	virtual void TakeDamage(int amount, Character* attacker = nullptr) override;

	void AddBuff(BuffInfo inBuff);	// 버프 추가 함수
	void ResetBuff();				// 버프한 스텟 초기화 함수

	// void UseItem(Item* item);	// 아이템 사용 함수

};