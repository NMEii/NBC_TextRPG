#pragma once
#include "BaseUI.h"


class InventoryUI : public BaseUI
{
public:

	InventoryUI();

	~InventoryUI(); 

	// 화면 그리기 
	virtual void Render() override;

	// 화면 업데이트 
	virtual void Update() override;

	// 메뉴 선택 처리 
	void OnSelect(int choice) override;

private:
	std::pair<Pos, Pos> range = { { 0,4 }, { 0,5 } };
	Pos pos = { 0,4 };

};

