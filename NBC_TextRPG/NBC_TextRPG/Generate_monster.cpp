#include "Generate_monster.h"
#include<ctime>
#include<cstdlib>

//random 돌리기 위한 참조 및 랜덤으로 돌렸을때 나올 몬스터 약 3,4종류로 고민중
std::vector<std::string> Generate_monster::monsterName = {
    "이름", "뭘로", "할까", "고민중"
};


Monster* Generate_monster::generate(int playerLevel)
{
    Monster* newMonster = nullptr;
    //보몬스터용 조건
    if (playerLevel == 10)
    {
        newMonster = new Monster("와 샌즈!", 20);
    }
    //일반 몬스터용
    else
    {
        int randomIndex = rand() % monsterName.size();
        std::string selectedName = monsterName[randomIndex];
        newMonster = new Monster(selectedName, playerLevel);
    }
    return newMonster;
}
