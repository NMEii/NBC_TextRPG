#pragma once
#include "BaseUI.h"

class MainMenuUI : public BaseUI
{
public:
	MainMenuUI(); 

	~MainMenuUI(); 

	// 화면 그리기 
	virtual void Render() override;

	// 화면 업데이트 
	virtual void Update() override;

	// 메뉴 선택 처리 
	void OnSelect(int choice) override;

private :

	virtual void InitUI() override; 


protected:

	void DrawCanvasRect(); 

	void DrawTitleRect(); 

	void DrawMenuRect(); 

	void DrawkeyRect(); 

	

private:

	UIRect menuRect; 
	UIRect KeyRect;
};

