#pragma once
#include "IMenu.h"

using namespace std;

enum ColorType {
    BLACK,  	//0
    DarkBLUE,	//1
    DarkGreen,	//2
    darkSkyBlue,    //3
    DarkRed,  	//4
    DarkPurple,	//5
    DarkYellow,	//6
    GRAY,		//7
    DarkGray,	//8
    BLUE,		//9
    GREEN,		//10
    SkyBlue,	//11
    RED,		//12
    PURPLE,		//13
    YELLOW,		//14
    WHITE		//15
};

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
    BaseUI();

    ~BaseUI();

    virtual void Render() override {}

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

    virtual void InitUI() {}

    void PrintColorString(int color, const string& str);

    void ClearRect(UIRect& rect); 

protected:
    vector<string> menus;

    UIRect canvasRect;
    UIRect titleRect;

    int selectedIndex = 0;
};

