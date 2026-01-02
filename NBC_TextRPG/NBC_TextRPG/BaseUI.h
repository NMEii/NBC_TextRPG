癤#pragma once
#include "IMenu.h"

using namespace std;

struct UIRect
{
    int x;
    int y;
    int width;
    int height;

    // 대 肄痢  移 (由 �)
    int InnerX() const { return x + 1; }
    int InnerY() const { return y + 1; }
    int InnerWidth()  const { return width - 2; }
    int InnerHeight() const { return height - 2; }
};

class BaseUI :public IMenu
{
public:
    /* 깆 */
    BaseUI();

    /* 硫몄 */
    ~BaseUI();


    /* 硫 洹몃━湲 ( 대ㅼ 援ы) */
    virtual void Render() override {}

    /* 硫 곗댄 ( 대ㅼ 援ы) */
    virtual void Update() override {}



    // 硫 명 愿由 
    // range : 踰 [1, range] 
    virtual int HandleInputByNums(int range) override;

    virtual bool HandleKeyInput(int& index, int range, bool isVertical = true);

    void Move(Pos TargetPos);

    // GM <-> 몄 

    virtual void OnSelect(int choice) = 0;


protected:

    /* 콘솔 지우기*/
    void ClearConsole(); 

    /* 콘솔 크기 구하기 */
    void GetConsoleSize(int& width, int& height);

    /*而ㅼ 대*/
    void SetCursorPos(int x, int y);

    /* 肄 以 援ы湲 */
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

