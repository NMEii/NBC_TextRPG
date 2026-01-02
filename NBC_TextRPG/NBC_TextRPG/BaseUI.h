#pragma once
#include "IMenu.h"

using namespace std; 

struct UIRect
{
    int x;
    int y;
    int width;
    int height;

    // 내부 콘텐츠 시작 위치 (테두리 제외)
    int InnerX() const { return x + 1; }
    int InnerY() const { return y + 1; }
    int InnerWidth()  const { return width - 2; }
    int InnerHeight() const { return height - 2; }
};

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

    virtual bool HandleKeyInput(int& index, int range, bool isVertical = true);

    void Move(Pos TargetPos);

    // GM <-> 상호작용 

    virtual void OnSelect(int choice) = 0; 


protected:

    /* 콘솔 지우기*/
    void ClearConsole(); 

    /* 콘솔 크기 구하기 */
    void GetConsoleSize(int& width, int& height);

    /*커서 이동*/
    void SetCursorPos(int x, int y); 

    /* 콘솔 중앙 구하기 */
    UIRect GetCenteredRect(int boxW, int boxH);

    void DrawRect(const UIRect r);

    /* x초 딜레이 */
    void Delay(float time); 

protected:
    vector<string> menus; 

    UIRect canvasRect;
    UIRect titleRect;

    int selectedIndex = 0; 
};

