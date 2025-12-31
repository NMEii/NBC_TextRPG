#pragma once
#include <string>
using namespace std;

class Status
{
public:
	Status(string name, int currenthealth, int maxhealth, int attack);

	string name;
	int currentHealth;
	int maxHealth;
	int attack;
	bool bIsDead = false;
};


