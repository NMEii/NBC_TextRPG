//Player.h
#pragma once
#include <string>
#include "Character.h"

class Player : public Character
{
private:
	static Player* instance; // 유일한 플레이어 객체를 가리키는 정적 포인터
	int iLevel;		// 레벨
	int iExp;		// 경험치
	int iGold;		// 골드
	int iBuffCount; // 공격력 버프 횟수

	// MaxHp/Hp : 200, Atk: 30
	Player(std::string name) :
		Character(Status(name, 200, 200, 30)),
		iLevel(1), iExp(0), iGold(0), iBuffCount(0)
	{
	}

public:
	// 복사 생성자 및 대입 연산자 삭제 (싱글톤 구현)
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* GetInstance(); // 싱글톤 인스턴스 반환 함수

	int GetLevel() const;	// 레벨 출력 함수
	int GetExp() const;		// 경험치 출력 함수
	int GetGold() const;	// 골드 출력 함수

	void EarnReward();	// 경험치, 골드 획득 함수
	void LevelUp();		// 레벨업 함수
	void ResetBuff();	// 버프한 스텟 초기화 함수

	void Attack(Character* monster);	// 공격 함수
	void UseItem();					// 아이템 사용 함수
};