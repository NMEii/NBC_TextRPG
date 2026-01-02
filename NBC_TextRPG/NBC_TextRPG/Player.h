//Player.h
#pragma once

#include "Character.h"

class Player : public Character
{
private:
	static Player* instance; // 유일한 플레이어 객체를 가리키는 정적 포인터
	int level;		// 레벨
	int exp;		// 경험치
	int gold;		// 골드
	// int buffCount;	// 공격력 버프 횟수

	Player(std::string name);

public:
	// 복사 생성자 및 대입 연산자 삭제 (싱글톤 구현)
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* GetInstance(); // 싱글톤 인스턴스 반환 함수

	int GetLevel() const;	// 레벨 출력 함수
	int GetExp() const;		// 경험치 출력 함수
	int GetGold() const;	// 골드 출력 함수

	void EarnReward();	// 보상 획득 함수
	void LevelUp();		// 레벨업 함수

	void TakeItem(double percent);	// 아이템 획득 함수 to EarnReward
	void TakeExp(int inExp);		// 경험치 증가 함수 to EarnReward
	void TakeGold(int inGold);		// 골드 증가 함수 to EarnReward

	// void GetAttackBuff(int amount); // 공격력 버프 함수 (버프 클래스 추가 후 구현)

	void Attack(Character* monster);	// 공격 함수
	// void UseItem(Item* item);		// 아이템 사용 함수
	// void ResetBuff();	// 버프한 스텟 초기화 함수

};