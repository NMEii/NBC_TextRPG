#include "pch.h"
#include "Player.h"

int Player::GetLevel() const {
	return iLevel;
}
int Player::GetExp() const {
	return iExp;
}
int Player::GetGold() const {
	return iGold;
}

void Player::GetReward(const int exp)
{
	iExp += exp;
	std::cout << exp << "의 경험치를 획득했습니다." << std::endl;
	while (iExp >= iLevel * 100) {
		iExp -= iLevel * 100;
		LevelUp();
	}
}
void Player::LevelUp()
{
	if (iLevel >= 10) {
		std::cout << "이미 최대 레벨입니다." << std::endl;
		return;
	}

	iLevel++;
	iMaxHp = iMaxHp + (iLevel * 20);
	iAtk = iAtk + (iLevel * 5);
	iHp = iMaxHp;
}
void Player::UseItem()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 9);
	auto randNum = dist(mt);
	std::cout << "아이템을 사용했습니다." << std::endl;
}