#include "pch.h"
#include "Character.h"

//stats에 초기화 필요
//Status(string name, int level, int currenthealth, int maxhealth, int attack)
//ex)Player
//Player 생성자 : Player() : Character( stats("John",1 , 200, 200, 30) )
Character::Character(Status stats) : stats(stats)
{
	
}