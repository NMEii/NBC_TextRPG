#include "pch.h"
#include "Character.h"
#include "Attack.h"

//stats에 초기화 필요
//Status(string name, int level, int currenthealth, int maxhealth, int attack)
//ex)Player
//Player 생성자 : Player() : Character( stats("John",1 , 200, 200, 30) )
Character::Character(Status stats) : stats(stats)
{
	//Player, Monster 생성자에 AddActions 추가 필요
	//AddActions(make_unique<Attack>());	// Player, Monster 둘 다 추가
	//AddActions(make_unique<UseItem>());	// Player만 추가
}

void Character::AddActions(unique_ptr<Action> action)
{
	actions.push_back(move(action));
}

void Character::PlayAction(size_t index, ActionContext& context)
{
	//owner를 이 함수를 호출하는 객체로 설정
	context.owner = this;

	//actions vector의 index 번호의 action을 실행
	actions[index]->Play(context);
}
