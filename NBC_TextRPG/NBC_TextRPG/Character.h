#pragma once
#include <vector>
#include <memory>

#include "Action.h"

using namespace std;

struct Status
{
	string name = "";
	int currentHealth = 0;
	int maxHealth = 0;
	int attack = 0 ;
	bool bIsDead = false;
};



class Character
{
public:
	Character(string InName);
	void AddActions(unique_ptr<Action> action);
	void PlayAction(size_t index, ActionContext& context);

	void TakeDamage(int amount);

	void DeadEvent();

	Status stats;
protected:
	vector<unique_ptr<Action>> actions;
};

