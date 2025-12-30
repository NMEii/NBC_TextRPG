#pragma once

class Character
{
public:
	string sName;
	int iHp;
	int iMaxHp;
	int iAtk;

	Character(string name, int maxHp, int hp, int atk) :
		sName(name), iMaxHp(maxHp), iHp(hp), iAtk(atk) {
	}

	string GetName() const {
		return sName;
	}
	int GetHp() const {
		return iHp;
	}
	void SetHp(int hp) {
		iHp = hp;
	}

	virtual void Attack(Character* monster) = 0;
	virtual void UseItem() = 0;
};

