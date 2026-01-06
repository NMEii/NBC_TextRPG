#include "pch.h"
#include "EndingCreditUI.h"

EndingCreditUI::EndingCreditUI()
{
    InitUI();
}

EndingCreditUI::~EndingCreditUI()
{
}

void EndingCreditUI::Render()
{
    DrawRect(canvasRect);

    for (int i = 0; i < credits.size(); i++)
    {
        if (bFinished)
        {
            SetCursorPos(canvasRect.InnerX() + (canvasRect.InnerWidth() / 2) - 10, canvasRect.InnerY() + (canvasRect.InnerHeight() / 2) + 5);
            PrintColorString(ColorType::Red, "Press Enter to Exit");
            break;
        }

        int y = static_cast<int>(scrollY) + i;

        if (y < canvasRect.InnerY() || y > canvasRect.InnerY() + canvasRect.InnerHeight())
            continue;

        int x = canvasRect.InnerX()+ (canvasRect.InnerWidth()/2) - credits[i].size() / 2;

        SetCursorPos(x, y);

        if (i == credits.size() - 1)
            PrintColorString(ColorType::Yellow, credits[i]);
        else
            cout << credits[i];

     
    }

}

void EndingCreditUI::Update()
{
    if (!bFinished)
    {
        scrollY -= scrollSpeed;

        if (scrollY + credits.size() <= 1)
            bFinished = true; 
    }
    else
    {
        int temp = 0; 
        if (HandleKeyInput(temp, 0))
        {
            if (OnRequest)
                OnRequest(UIRequest::OpenMainMenu);
        }
    }
}

void EndingCreditUI::OnSelect(int choice)
{
}

void EndingCreditUI::InitUI()
{
    ClearConsole(); 

    credits = {
        "",
        "",
        "=== ENDING CREDIT ===",
        "",
        "",
        "병권 몬스터",
        "",
        "======================",
        "",
        "",
        "Team leader & Monster Design",
        "황병권",
        "",
        "",
        "",
        "Project Manager",
        "권민성",
        "",
        "",
        "",
        "Combat System Part",
        "이준로"
        "",
        "",
        "",
        "Chacter Design Part",
        "박하민",
        "",
        "",
        "",
        "Git Management & Inventory & AudioManager Part ",
        "김남태",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        R"( .-') _     ('-.   ('-.     _   .-')         ('-.        )",
        R"((  OO) )  _(  OO) ( OO ).-.( '.( OO )_      ( OO )       )",
        R"(/     '._(,------./ . --. / ,--.   ,--.)  .---. .-----.  )",
        R"(|'--...__)|  .---'| \-.  \  |   `.'   |  /_   |/  -.   \ )",
        R"('--.  .--'|  |  .-'-'  |  | |         |   |   |'-' _'  | )",
        R"(   |  |  (|  '--.\| |_.'  | |  |'.'|  |   |   |   |_  <  )",
        R"(   |  |   |  .--' |  .-.  | |  |   |  |   |   |.-.  |  | )",
        R"(   |  |   |  `---.|  | |  | |  |   |  |   |   |\ `-'   / )",
        R"(   `--'   `------'`--' `--' `--'   `--'    `---' `----'' )",
        "Thanks for Playing!"
    };
    scrollY = canvasRect.InnerY()  + credits.size();
}
