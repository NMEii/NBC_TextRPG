#pragma once
#include <string>
using namespace std;

class Status
{
public:
	Status(string name, int level, int currenthealth, int maxhealth, int attack) {}


	string Name;
	int level;
	int currentHealth;
	int maxHealth;
	int attack;
	bool bIsDead = false;
};


