#include "pch.h"
#include "GameManager.h"


int main()
{
    // 랜덤 시드 초기화 
    srand(time(0)); 

    // 게임 매니저 생성 
    std::unique_ptr<GameManager> GM = std::make_unique<GameManager>();

    // 게임 루프 
    GM->StartGame(); 

}

