#pragma once
#include <vector>
#include <memory>
#include "Status.h"
#include "Action.h"

using namespace std;

class Character 
{
public:
	Character(Status stats);
	void AddActions(unique_ptr<Action> action);
	void PlayAction(size_t index, Character* target);

	Status stats;
protected:
	vector<unique_ptr<Action>> actions;
};

