// Player.cpp
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

		switch (Choice(0, 2))
		{
		case 0:
			selectWeapon = WeaponType::Sniper;
			break;
		case 1:
			selectWeapon = WeaponType::DualGun;
			break;
		case 2:
			selectWeapon = WeaponType::Armor;
			break;
		}

		instance = new Player("병권", selectWeapon);
	}
	return instance;
}

string Player::GetWeaponName() const
{
	switch (myWeaponType)
	{
	case WeaponType::Sniper:
		return "스나이퍼";
	case WeaponType::DualGun:
		return "쌍병건";
	case WeaponType::Armor:
		return "방어구";
	}
}

void Player::LevelUp()
{
	level++;
	stats.maxHealth += (level * 20);
	stats.attack += (level * 5);
	stats.currentHealth = stats.maxHealth;
}

void Player::IncreaseExp(int inExp)
{
	if (level >= 10) return;
	// cout << "최대 레벨에 도달하여 더 이상 경험치를 획득할 수 없습니다.\n";

	// cout << "+" << inExp << "EXP\n";
	exp += inExp;

	if (exp >= 100)
	{
		exp -= 100;
		LevelUp();
	}
}

void Player::Attack(Character* target)
{
	if (target == nullptr) return;

	ActionContext context;
	context.target = target;
	context.ownerPlayer = this;

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
		// cout << "공격력이 " << inBuff.value << "만큼 증가했습니다.\n";
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
			// cout << "전투가 종료되어 공격력이 원래대로 돌아왔습니다.\n";
		}
	}

	buffs.clear();
}

void Player::UseItem(Item* item) // (전투 중 랜덤으로 아이템 사용하도록 추가 필요)
{
	if (item == nullptr) return;
	ActionContext context;
	context.ownerPlayer = this;
	context.useItem = item;

	PlayAction(1, context);
}

const vector<string>& Player::GetCharacterImage()
{
	return PlayerImage;
}

const vector<string> Player::PlayerImage = {
	R"(         ____)",
	R"(     _-"     "\)",
	R"(   _/          |_)",
	R"(  "{      _______\___)",
	R"(   \__/uuuuu|"""}--"   )",
	R"(   {uuuuuuu_/ ㅇ\" )",
	R"(    \______/ *__} )",
	R"(    ___}___  __/   )",
	R"(   /       \- \_    __ )",
	R"(  |         | / \  /  \)",
	R"( /--ㅁ-------||  \|-   ])",
	R"(|          / \    |\   ))",
	R"(|         |  /\     \_/)",
	R"( \-_____-/  /  \ ____/)" };


// void Player::SetKillLog(const string& monsterName)
//{
//	killLog[monsterName]++;
//	cout << monsterName << "을(를) 처치했습니다! 총 " << killLog[monsterName] << "마리 잡음.\n";
// }
// void Player::GetKillLog() const
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
// }
