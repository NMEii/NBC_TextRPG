//Player.cpp
#include "pch.h"
#include "Random.h"
#include "Player.h"

using namespace std;
using namespace Random;

Player* Player::instance = nullptr; // 정적 멤버 초기화

Player* Player::GetInstance()
{
	if (instance == nullptr) {
		cout << "플레이어 이름을 입력하세요: ";
		string name;
		getline(cin, name);

		if (name.empty()) // 빈 값 입력 시 기본 이름 설정
		{
			cout << "이름이 입력되지 않아 기본 이름 'Steve'로 설정됩니다.\n";
			name = "Steve";
		}
		instance = new Player(name);
	}
	return instance;
}

int Player::GetLevel() const { return iLevel; }
int Player::GetExp() const { return iExp; }
int Player::GetGold() const { return iGold; }

void Player::EarnReward()
{
	int gold = Choice(10, 20); // 골드 범위 10~20
	cout << gold << " 골드를 획득했습니다.\n";
	iGold += gold;

	if (Success(0.3)) // 아이템 획득 확률 30%
	{
		cout << "공격력 증가 아이템을 획득했습니다.\n";
		/* (아이템 획득 함수 추후 구현)
		GetItem(); */
	}

	if (iLevel >= 10)
	{
		cout << "최대 레벨에 도달하여 더 이상 경험치를 획득할 수 없습니다.\n";
		return;
	}

	int exp = 50; // 고정 경험치 값
	cout << exp << "의 경험치를 획득했습니다.\n";
	iExp += exp;

	if (iExp >= 100)
	{
		iExp -= 100;
		LevelUp();
	}
}
void Player::LevelUp()
{
	cout << "레벨 업!\n";
	iLevel++;
	stats.iMaxHp = stats.iMaxHp + (iLevel * 20);
	stats.iAtk = stats.iAtk + (iLevel * 5);
	stats.iHp = stats.iMaxHp;
}
void Player::ResetBuff()
{
	if (iBuffCount > 0)
	{
		stats.iAtk -= (10 * iBuffCount);
		iBuffCount = 0;
		cout << "전투가 종료되어 공격력이 원래대로 돌아왔습니다.\n";
	}
}

void Player::Attack(Character* monster) /* (몬스터 이름 및 체력 추후 인자로 받도록 수정 필요) */
{
	if (monster == nullptr) return;

	cout << monster->stats.sName << "에게 " << stats.iAtk << "의 데미지를 입혔습니다.\n";
	monster->stats.iHp -= stats.iAtk;
}
void Player::UseItem() /* (전투 중 랜덤으로 아이템 사용하도록 추가 필요) */
{
	int itemType = Choice(0, 1); // 0: 체력 회복 아이템, 1: 공격력 증가 아이템

	if (itemType == 0) // 체력 회복
	{
		int healAmount = 50; // 고정 회복량
		stats.iHp += healAmount;

		if (stats.iHp > stats.iMaxHp)
		{
			healAmount -= (stats.iHp - stats.iMaxHp);
			stats.iHp = stats.iMaxHp;
		}
		cout << "[아이템 사용] 포션을 사용하여 체력이" << healAmount << "회복되었습니다.\n";
	}
	else // 공격력 증가 (이번 전투만)
	{
		int atkBuffAmount = 10; // 고정 공격력 증가량
		iBuffCount++;			// 버프 횟수 기록
		stats.iAtk += atkBuffAmount;
		cout << "[아이템 사용] 공격력 증가 아이템을 사용하여 공격력이 " << atkBuffAmount << " 증가했습니다!\n";
	}
}