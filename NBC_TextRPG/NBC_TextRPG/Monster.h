#pragma once
#include"Character.h"

class Monster :public Character
{
public:
	Monster(std::string name, int level);
	virtual ~Monster() {}

	void takeDamage(int damage)	override;
	
	//virtual void draw();
};