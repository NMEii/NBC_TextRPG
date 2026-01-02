#pragma once
#include <string>
using namespace std;

class Status
{
public:
	Status(string inName , int HP = 0, int inAttack = 0);

	string name;
	int currentHealth;
	int maxHealth;
	int attack;
	bool bIsDead = false;
};


