#pragma once

using namespace std;

class Action;
struct ActionContext;

struct Status
{
	string name = "";
	int currentHealth = 0;
	int maxHealth = 0;
	int attack = 0;
	bool bIsDead = false;
};

class Character
{
public:
	Character();
	Character(string InName);
	void AddActions(unique_ptr<Action> action);
	void PlayAction(size_t index, ActionContext& context);

	virtual void TakeDamage(int amount, Character* attacker = nullptr);

	void DeadEvent();

	//void printImage(int index);

	Status stats;
protected:
	vector<unique_ptr<Action>> actions;
};

