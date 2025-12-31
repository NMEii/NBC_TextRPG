#include "pch.h"
#include "GameManager.h"

// 메인 
// 게임의 시작점 

int main()
{
    // 랜덤 시드 초기화 
    srand(unsigned int(time(0))); 

    // 게임 매니저 생성 
    std::unique_ptr<GameManager> GM = std::make_unique<GameManager>();

    // 게임 루프 
    GM->StartGame(); 

}

