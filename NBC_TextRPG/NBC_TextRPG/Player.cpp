//Player.cpp
#include "pch.h"
#include "Random.h"
#include "Player.h"
#include "AttackAction.h"
#include "UseItemAction.h"

using namespace std;
using namespace Random;

Player::Player(string name) : Character(name)
{
	/* (이름 설정은 외부에서 호출할 때 아래 코드를 설정)
	cout << "플레이어 이름을 입력하세요: ";
	string name;
	getline(cin, name);

	if (name.empty()) // 빈 값 입력 시 기본 이름 설정
	{
		cout << "이름이 입력되지 않아 기본 이름 'Steve'로 설정됩니다.\n";
		name = "Steve";
	}*/

	level = 1;
	exp = 0;
	gold = 0;

	stats.maxHealth = 200;
	stats.attack = 30;

	WeaponType selectWeapon = WeaponType::DualGun;
	string weaponName;

	switch (Choice(0, 2))
	{
	case 0:
		weaponName = "스나이퍼";
		selectWeapon = WeaponType::Sniper;
		stats.attack += 20;
		stats.maxHealth -= 50;
		break;
	case 1:
		weaponName = "듀얼건";
		selectWeapon = WeaponType::DualGun;
		break;
	case 2:
		weaponName = "방어구";
		selectWeapon = WeaponType::Armor;
		stats.maxHealth += 100;
		stats.attack -= 10;
		break;
	}

	stats.currentHealth = stats.maxHealth;

	cout << "눈 앞에 떨어져 있는 " << weaponName << "을(를) 주웠습니다.\n";
	myWeapon = selectWeapon;

	AddActions(make_unique<AttackAction>());
	AddActions(make_unique<UseItemAction>());
}

int Player::GetLevel() const { return level; }
int Player::GetExp() const { return exp; }
int Player::GetGold() const { return gold; }

void Player::LevelUp()
{
	cout << "레벨 업!\n";
	level++;
	stats.maxHealth += (level * 20);
	stats.attack += (level * 5);
	stats.currentHealth = stats.maxHealth;
}

void Player::EarnReward()
{
	const double percent = 0.3;		// 아이템 획득 확률 (현재 30%)
	const int inExp = 50;			// 획득 경험치

	TakeItem(percent);
	TakeExp(inExp);
	TakeGold(Choice(10, 20));		// 획득 골드 범위 (현재 10~20)
}

void Player::TakeItem(double percent)
{
	if (Success(percent)) // 아이템 획득 확률 30%
	{
		cout << "아이템을 획득했습니다. (함수 추후 구현)\n";
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

	cout << "+" << inExp << "EXP\n";
	exp += inExp;

	if (exp >= 100)
	{
		exp -= 100;
		LevelUp();
	}
}

void Player::TakeGold(int inGold)
{
	cout << "+" << inGold << " Gold\n";
	gold += inGold;
}

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

/* (몬스터 이름 및 체력 추후 인자로 받도록 수정 필요) */
void Player::Attack(Character* monster)
{
	if (monster == nullptr) return;

	int finalDamage = stats.attack;

	if (myWeapon == WeaponType::Sniper && Success(0.3)) // 스나이퍼일 때, 크리티컬 확률 30%
	{
		finalDamage *= 2;
		cout << "[패시브: 크리티컬] 치명타가 터졌습니다!\n";
	}

	cout << monster->stats.name << "에게 " << finalDamage << "의 데미지를 입혔습니다.\n";

	/* PlayAction을 이용한 Attack은 stat.attack 고정이라 임시로 이용 */
	monster->TakeDamage(finalDamage);

	if (!monster->stats.bIsDead && myWeapon == WeaponType::DualGun && Success(0.3)) // 듀얼건일 때, 연속 사격 확률 30%
	{
		cout << "[패시브: 연속 사격] 한 번 더 공격합니다!\n";
		monster->TakeDamage(finalDamage);
	}

	if (monster->stats.bIsDead)
	{
		SetKillLog(monster->stats.name);
		EarnReward();
	}
}

void Player::GetDamage(int amount, Character* monster)
{
	TakeDamage(amount);

	if (myWeapon == WeaponType::Armor && !stats.bIsDead && monster != nullptr)	// 아머일 때, 반사 데미지
	{
		int reflectDamage = (amount * Choice(0, 100)) / 100;	// 랜덤한 데미지 반사 (0 ~ 100%)

		if (reflectDamage <= 0) return;

		cout << "[패시브: 반사] " << monster->stats.name << "에게 " << reflectDamage << "의 반사 데미지를 입혔습니다.\n";
		monster->TakeDamage(reflectDamage);

		if (monster->stats.bIsDead)
		{
			SetKillLog(monster->stats.name);
			EarnReward();
		}
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
		switch (b.type)
		{
		case BuffType::AttackUp:
			stats.attack -= b.value;
			cout << "- " << b.name << " 효과 종료\n";
			break;
		}
	}

	buffs.clear();
}

/* // 아이템 사용 참조 코드
void Player::UseItem(Item* item) // (전투 중 랜덤으로 아이템 사용하도록 추가 필요)
{
	if (item == nullptr) return;

	ActionContext context;
	context.useItem = item;

	PlayAction(1, context);
	buffCount++; // 버프 횟수 기록
}

	// 랜덤으로 아이템 선택 참조 코드
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