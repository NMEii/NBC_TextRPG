#pragma once
#include "IMenu.h"

using namespace std; 

class BaseUI :public IMenu
{
public:
    /* 생성자 */
    BaseUI();

    /* 소멸자 */
    ~BaseUI();
  

    /* 화면 그리기 (자식 클래스에서 구현) */
    virtual void Render() override {}

    /* 화면 업데이트 (자식 클래스에서 구현) */
    virtual void Update() override {}

    // 메뉴 인풋 관리 
    // range : 범위 [1, range] 
    virtual int HandleInputByNums(int range) override; 

    virtual bool HandleKeyInput(Pos& pos,const std::pair<Pos, Pos> Range);

    virtual void OnSelect(int choice) = 0; 

    void Move(Pos TargetPos); 

protected:

    /* 콘솔 지우기*/
    void ClearConsole(); 

protected:
    vector<string> menus; 

    int selectedIndex = 0; 
};

