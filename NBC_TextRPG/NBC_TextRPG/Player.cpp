//Player.cpp
#include "pch.h"
#include "Random.h"
#include "Player.h"
#include "AttackAction.h"
#include "UseItemAction.h"
#include "Inventory.h"
#include "Buff.h"
/* 각 무기 헤더 및 스텟 조정은 추후 별도의 로직으로 분리 */
#include "Sniper.h"   
#include "DualGun.h"
#include "Armor.h"

using namespace std;
using namespace Random;

Player::Player(string name, WeaponType weapon)
	: Character(name), myWeaponType(weapon)
{
	level = 1;
	exp = 0;

	stats.maxHealth = 200;
	stats.attack = 30;

	switch (weapon)
	{
	case WeaponType::Sniper:
		myWeapon = make_unique<Sniper>();
		stats.attack += 20;
		stats.maxHealth -= 50;
		break;
	case WeaponType::DualGun:
		myWeapon = make_unique<DualGun>();
		break;
	case WeaponType::Armor:
		myWeapon = make_unique<Armor>();
		stats.maxHealth += 100;
		stats.attack -= 10;
		break;
	}

	stats.currentHealth = stats.maxHealth;

	inventory = new Inventory();

	AddActions(make_unique<AttackAction>());
	AddActions(make_unique<UseItemAction>());
}

Player* Player::instance = nullptr; // 정적 멤버 초기화

Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		WeaponType selectWeapon = WeaponType::DualGun;
		string weapon;

		switch (Choice(0, 2))
		{
		case 0:
			weapon = "스나이퍼";
			selectWeapon = WeaponType::Sniper;
			break;
		case 1:
			weapon = "듀얼건";
			selectWeapon = WeaponType::DualGun;
			break;
		case 2:
			weapon = "방어구";
			selectWeapon = WeaponType::Armor;
			break;
		}

		//cout << "눈 앞에 떨어져 있는 " << weapon << "을(를) 주웠습니다.\n";
		instance = new Player("병권", selectWeapon);
	}
	return instance;
}

//void Player::SetKillLog(const string& monsterName)
//{
//	killLog[monsterName]++;
//	cout << monsterName << "을(를) 처치했습니다! 총 " << killLog[monsterName] << "마리 잡음.\n";
//}
//void Player::GetKillLog() const
//{
//	cout << "=== 잡은 몬스터 기록 ===\n";
//	if (killLog.empty())
//	{
//		cout << "아직 잡은 몬스터가 없습니다.\n";
//		return;
//	}
//	for (const auto& log : killLog)
//	{
//		cout << log.first << " : " << log.second << "마리\n";
//	}
//	cout << "=====================\n";
//}

void Player::LevelUp()
{
	//cout << "레벨 업!\n";
	level++;
	stats.maxHealth += (level * 20);
	stats.attack += (level * 5);
	stats.currentHealth = stats.maxHealth;
}

void Player::AquireItem(Item* item)
{
	const double percent = 0.3; // 아이템 획득 확률 (현재 30%)
	if (Success(percent))
		inventory->AddItem(item, 1);
}

void Player::IncreaseExp(int inExp)
{
	const int iExp = 50; // 획득 경험치 (현재 50)

	if (level >= 10)
	{
		// cout << "최대 레벨에 도달하여 더 이상 경험치를 획득할 수 없습니다.\n";
		return;
	}

	// cout << "+" << inExp << "EXP\n";
	exp += iExp;

	if (exp >= 100)
	{
		exp -= 100;
		LevelUp();
	}
}

/* (몬스터 이름 및 체력 추후 인자로 받도록 수정 필요) */
void Player::Attack(Character* target)
{
	if (target == nullptr)
		return;

	ActionContext context;
	context.target = target;
	PlayAction(0, context);
}

void Player::TakeDamage(int amount, Character* attacker)
{
	Character::TakeDamage(amount);

	if (!stats.bIsDead && myWeapon && attacker)
	{
		myWeapon->OnTakeDamage(this, attacker, amount);
	}
}

void Player::AddBuff(BuffInfo inBuff)
{
	buffs.push_back(inBuff);

	switch (inBuff.type)
	{
	case BuffType::AttackUp:
		stats.attack += inBuff.value;
		//cout << "공격력이 " << inBuff.value << "만큼 증가했습니다.\n";
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
			//cout << "전투가 종료되어 공격력이 원래대로 돌아왔습니다.\n";
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

