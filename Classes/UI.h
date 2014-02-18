#ifndef __UI_H__
#define __UI_H__

#define UI_NONE 0
#define UI_MAINMENU 1
#define UI_INGAME 2
#define UI_LEVELEDITOR 3

#define ACTIVATEUI(A, B) UI::Get()->setUINode(A, B)
#define DEACTIVATEUI UI::Get()->setUINode(nullptr)
#define UPDATEUI UI::Get()->update()

#define ACTIVATEBASEUI(A) ACTIVATEUI(A, UI_NONE);
#define ACTIVATEMAINMENUUI(A) UI::Get()->pMainMenu = A; ACTIVATEUI(A, UI_MAINMENU);
#define ACTIVATEINGAMEUI(A) UI::Get()->pHelloWorld = A; ACTIVATEUI(A, UI_INGAME);
#define ACTIVATELEVELEDITORUI(A) UI::Get()->pLevelEditor = (LevelEditor*)A; ACTIVATEUI(A, UI_LEVELEDITOR);

#include "Singleton.h"
#include "cocos2d.h"
#include "LevelEditor.h"
#include <vector>

class CMainMenu;
class HelloWorld;

USING_NS_CC;
using namespace std;

class UI : public TSingleton<UI>
{
public:
	UI(void);
	virtual ~UI(void);

	CMainMenu* pMainMenu;
	HelloWorld* pHelloWorld;
	LevelEditor* pLevelEditor;

	void setUINode(Node* _pNode, int _menu);
	void update();
	void nullCallback();
private:
	Node* m_pUINode;
	Node* m_pCommon;
	Node* m_pMenu;
	Node* m_pIngame;
	Node* m_pLevelEditor;
	bool active;
	vector<string> getAllFilesInFolder(string folder);
	wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
	void createLevelEditorFilePopup();
	void createLevelEditorUI();
	void createCommonUI();
	void createMainMenuUI();
	void createIngameUI();
};

#endif//__UI_H__