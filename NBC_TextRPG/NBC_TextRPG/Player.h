#pragma once
#include "pch.h"
#include <iostream>
#include "Character.h"

using namespace std;

class Player : public Character
{
private:
	static Player* instance; // 유일한 플레이어 객체를 가리키는 정적 포인터
	int iLevel = 1; // 플레이어 레벨
	int iExp = 0; // 플레이어 경험치
	int iGold = 0; // 플레이어 골드

	Player(string name = "Steve") : Character(name, 200, 200, 30) {} // MaxHp/Hp : 200, Atk: 30

public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static Player* GetInstance() {
		if (instance == nullptr) {
			cout << "플레이어 이름을 입력하세요: ";
			string name;
			getline(cin, name);
			if (!name.empty())
				instance = new Player(name);
		}
		return instance;
	}

	int GetLevel() const; // 레벨 출력 함수
	int GetExp() const; // 경험치 출력 함수
	int GetGold() const; // 골드 출력 함수

	void GetReward(const int exp); // 경험치 획득 함수 (추가 구현에서 골드 획득 포함 예정)
	void LevelUp(); // 레벨업 함수
	void UseItem(); // 아이템 사용 함수

	virtual void attack() override; // 공격 함수
};

