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
	Status stats;
protected:
	vector<unique_ptr<Action>> Actions;
};

