#pragma once


enum class UIRequest;
class BaseUI; 
 
class CombatUI;
class MainMenuUI; 
class InventoryUI; 
class ItemShopUI;
class EndingCreditUI;

class Player;
using namespace std;

class GameManager
{
public:
	/*생성자*/
	GameManager(); 
	/*소멸자*/
	~GameManager(); 

#pragma region Game Manage
public:
	/* 게임 루프 관리 */
	void StartGame();

private:
	// 메인 루프 유지 
	bool bIsRunning;


private:
	/* 게임 초기화 */
	void Initialize();

	/* 업데이트 */
	void Update();

	/* 화면 그리기 */
	void Render(); 

	/* 게임 종료*/
	void ShutDown(); 
#pragma endregion 

#pragma region Console Manage 
private:
	/* 딜레이 주기 */
	void Delay(float Time); 

	/* 콘솔 지우기*/
	void ClearConsole(); 

#pragma endregion 

#pragma region UI Manage 
private:
	// UI 이벤트 바인드 
	void BindUIEvents(); 

	/* UI Request 관리 */
	void HandleUIRequest(UIRequest req);

	void SetCurrentUI(BaseUI* newUI); 

	void ResetUI(unique_ptr<BaseUI>& ui);
private:

	// 현재 메뉴 UI 
	BaseUI* currentMenu;
 
	unique_ptr<CombatUI> combatUI; 
	unique_ptr<MainMenuUI> mainMenuUI;
	unique_ptr<InventoryUI> inventoryUI;
	unique_ptr<ItemShopUI> itemShopUI;
	unique_ptr<EndingCreditUI> endingCreditUI; 

#pragma endregion

private:
	Player* player; 
};

