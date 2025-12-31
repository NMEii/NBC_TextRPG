//Player.cpp
#include "pch.h"
#include "Random.h"
#include "Player.h"
#include "Attack.h"

using namespace std;
using namespace Random;

// MaxHp/Hp : 200, Atk: 30
Player::Player(string name)
	: Character(Status(name, 200, 200, 30)), level(1), exp(0), gold(0), buffCount(0)
{
	AddActions(make_unique<Attack>());
}

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

int Player::GetLevel() const { return level; }
int Player::GetExp() const { return exp; }
int Player::GetGold() const { return gold; }

void Player::EarnReward()
{
	int earnGold = Choice(10, 20); // 골드 범위 10~20
	cout << earnGold << " 골드를 획득했습니다.\n";
	gold += earnGold;

	if (Success(0.3)) // 아이템 획득 확률 30%
	{
		cout << "공격력 증가 아이템을 획득했습니다.\n";
		/* (아이템 획득 함수 추후 구현)
		GetItem(); */
	}

	if (level >= 10)
	{
		cout << "최대 레벨에 도달하여 더 이상 경험치를 획득할 수 없습니다.\n";
		return;
	}

	int earnExp = 50; // 고정 경험치 값
	cout << earnExp << "의 경험치를 획득했습니다.\n";
	exp += earnExp;

	if (exp >= 100)
	{
		exp -= 100;
		LevelUp();
	}
}
void Player::LevelUp()
{
	cout << "레벨 업!\n";
	level++;
	stats.maxHealth = stats.maxHealth + (level * 20);
	stats.attack = stats.attack + (level * 5);
	stats.currentHealth = stats.maxHealth;
}
void Player::ResetBuff()
{
	if (buffCount > 0)
	{
		stats.attack -= (10 * buffCount);
		buffCount = 0;
		cout << "전투가 종료되어 공격력이 원래대로 돌아왔습니다.\n";
	}
}

void Player::Attack(Character* monster) /* (몬스터 이름 및 체력 추후 인자로 받도록 수정 필요) */
{
	if (monster == nullptr) return;

	cout << monster->stats.name << "에게 " << stats.attack << "의 데미지를 입혔습니다.\n";

	ActionContext context;
	context.target = monster;

	PlayAction(0, context);
}
void Player::UseItem() /* (전투 중 랜덤으로 아이템 사용하도록 추가 필요) */
{
	int itemType = Choice(0, 1); // 0: 체력 회복 아이템, 1: 공격력 증가 아이템

	if (itemType == 0) // 체력 회복
	{
		int healAmount = 50; // 고정 회복량
		stats.currentHealth += healAmount;

		if (stats.currentHealth > stats.maxHealth)
		{
			healAmount -= (stats.currentHealth - stats.maxHealth);
			stats.currentHealth = stats.maxHealth;
		}
		cout << "[아이템 사용] 포션을 사용하여 체력이" << healAmount << "회복되었습니다.\n";
	}
	else // 공격력 증가 (이번 전투만)
	{
		int atkBuffAmount = 10; // 고정 공격력 증가량
		buffCount++;			// 버프 횟수 기록
		stats.attack += atkBuffAmount;
		cout << "[아이템 사용] 공격력 증가 아이템을 사용하여 공격력이 " << atkBuffAmount << " 증가했습니다!\n";
	}
}