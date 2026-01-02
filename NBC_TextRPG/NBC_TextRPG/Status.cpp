#include "pch.h"
#include "Status.h"


Status::Status(string inName,  int HP, int inAttack)
	: name(inName)
{
	currentHealth = HP;
	maxHealth = HP;

	attack = inAttack;
}


// header < 