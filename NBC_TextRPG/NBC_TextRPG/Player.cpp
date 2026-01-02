//Player.cpp
#include "pch.h"
#include "Random.h"
#include "Player.h"
#include "AttackAction.h"
#include "UseItemAction.h"

using namespace std;
using namespace Random;

Player::Player(string name)
	: Character(name)
{
	level = 1;
	exp = 0;
	gold = 0;

	stats.maxHealth = 200;
	stats.currentHealth = stats.maxHealth;
	stats.attack = 30;

	AddActions(make_unique<AttackAction>());
	AddActions(make_unique<UseItemAction>());
}

Player* Player::instance = nullptr; // 정적 멤버 초기화

Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
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

void Player::SetKillLog(const string& monsterName)
{
	killLog[monsterName]++;
	cout << monsterName << "을(를) 처치했습니다! 총 " << killLog[monsterName] << "마리 잡음.\n";
}
void Player::GetKillLog() const
{
	cout << "=== 잡은 몬스터 기록 ===\n";
	if (killLog.empty())
	{
		cout << "아직 잡은 몬스터가 없습니다.\n";
		return;
	}
	for (const auto& log : killLog)
	{
		cout << log.first << " : " << log.second << "마리\n";
	}
	cout << "=====================\n";
}

void Player::EarnReward()
{
	double percent = 0.3;		// 아이템 획득 확률 (현재 30%)
	int inExp = 50;				// 획득 경험치
	int inGold = Choice(10, 20);// 획득 골드 범위 (현재 10~20)

	TakeItem(percent);
	TakeExp(inExp);
	TakeGold(inGold);
}
void Player::LevelUp()
{
	cout << "레벨 업!\n";
	level++;
	stats.maxHealth += (level * 20);
	stats.attack += (level * 5);
	stats.currentHealth = stats.maxHealth;
}

void Player::TakeItem(double percent)
{
	if (Success(percent)) // 아이템 획득 확률 30%
	{
		cout << "공격력 증가 아이템을 획득했습니다.\n";
		/* (아이템 획득 함수 추후 구현)
		GetItem(); */
	}
}
void Player::TakeExp(int inExp)
{
	if (level >= 10)
	{
		cout << "최대 레벨에 도달하여 더 이상 경험치를 획득할 수 없습니다.\n";
		return;
	}

	cout << inExp << "의 경험치를 획득했습니다.\n";
	exp += inExp;

	if (exp >= 100)
	{
		exp -= 100;
		LevelUp();
	}
}
void Player::TakeGold(int inGold)
{
	cout << inGold << " 골드를 획득했습니다.\n";
	gold += inGold;
}

/* (몬스터 이름 및 체력 추후 인자로 받도록 수정 필요) */
void Player::Attack(Character* monster)
{
	if (monster == nullptr) return;

	cout << monster->stats.name << "에게 " << stats.attack << "의 데미지를 입혔습니다.\n";

	ActionContext context;
	context.target = monster;

	PlayAction(0, context);

	if (monster->stats.bIsDead)
	{
		SetKillLog(monster->stats.name);
		EarnReward();
	}
}

void Player::AddBuff(BuffInfo inBuff)
{
	buffs.push_back(inBuff);

	switch (inBuff.type)
	{
	case BuffType::AttackUp:
		stats.attack += inBuff.value;
		cout << "공격력이 " << inBuff.value << "만큼 증가했습니다.\n";
		break;
	}
}

void Player::ResetBuff() /* 전투 종료 시 초기화되도록 호출 필요 */
{
	if (buffs.empty()) return;

	for (const auto& b : buffs)
	{
		if (b.type == BuffType::AttackUp)
		{
			stats.attack -= b.value;
			cout << "전투가 종료되어 공격력이 원래대로 돌아왔습니다.\n";
		}
	}

	buffs.clear();
}

/*void Player::UseItem(Item* item) // (전투 중 랜덤으로 아이템 사용하도록 추가 필요)
{
	if (item == nullptr) return;

	ActionContext context;
	context.useItem = item;

	PlayAction(1, context);
	buffCount++; // 버프 횟수 기록
}

	// 아이템 사용 참조 코드
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
*/