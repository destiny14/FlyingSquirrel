#ifndef __UI_H__
#define __UI_H__

#define UI_NONE 0
#define UI_MAINMENU 1
#define UI_INGAME 2
#define UI_LEVELEDITOR 3
#define UI_FILECHOOSER 4

#define ACTIVATEUI(A, B) UI::Get()->setUINode(A, B)
#define DEACTIVATEUI UI::Get()->setUINode(nullptr, UI_NONE)
#define UPDATEUI UI::Get()->update()

#define ACTIVATEBASEUI(A) ACTIVATEUI(A, UI_NONE);
#define ACTIVATEMAINMENUUI(A) UI::Get()->pMainMenu = A; ACTIVATEUI(A, UI_MAINMENU);
#define ACTIVATEINGAMEUI(A) UI::Get()->pHelloWorld = A; ACTIVATEUI(A, UI_INGAME);
#define ACTIVATELEVELEDITORUI(A) UI::Get()->pLevelEditor = (LevelEditor*)A; ACTIVATEUI(A, UI_LEVELEDITOR);
#define ACTIVATEFILECHOOSERMENU(A, B) UI::Get()->pLevelEditor = (LevelEditor*)A; UI::Get()->levelType = (int)B; UI::Get()->setUINode(A, UI_FILECHOOSER);

#include "Singleton.h"
#include "cocos2d.h"
#include "LevelEditor.h"
#include <vector>

class Player;
class CMainMenu;
class MainLayer;

USING_NS_CC;
using namespace std;

class UI : public TSingleton<UI>
{
public:
	UI(void);
	virtual ~UI(void);

	CMainMenu* pMainMenu;
	MainLayer* pHelloWorld;
	LevelEditor* pLevelEditor;
	int levelType;

	void setUINode(Node* _pNode, int _menu);
	void update();
	void nullCallback();
private:
	Node* m_pUINode;
	Node* m_pCommon;
	Node* m_pMenu;
	Node* m_pIngame;
	Node* m_pLevelEditor;
	LabelTTF* m_pGameOver;
	LabelTTF* m_playerMuni;
	Player* m_pPlayer;
	Sprite** m_pPlayerLife;
	Sprite** m_pCrystals;
	Sprite* m_crystal;
	Sprite* m_polle;
	int lastLife;
	int lastCrystal;
	int lastMuni;
	bool active;

	vector<string> getAllFilesInFolder(string folder);
	wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
	void createLevelEditorFilePopup();
	void createLevelEditorUI();
	void createCommonUI();
	void createMainMenuUI();
	void createIngameUI();
	void createMuniLabel();
};

#endif//__UI_H__