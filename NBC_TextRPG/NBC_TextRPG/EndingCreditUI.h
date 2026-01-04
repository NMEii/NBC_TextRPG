#pragma once
#include "BaseUI.h"

class EndingCreditUI : public BaseUI 
{
public:
	EndingCreditUI();

	~EndingCreditUI();

	virtual void Render() override;

	virtual void Update() override;

	void OnSelect(int choice) override;

private:

	virtual void InitUI() override;

protected:

	void DrawCanvasRect();

private:
	vector<string> credits; 

	float scrollY;
	float scrollSpeed = 0.1f;

	bool bFinished = false; 

};

