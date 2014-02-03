#ifndef __UI_H__
#define __UI_H__

#define UI_NONE 0
#define UI_MAINMENU 1
#define UI_INGAME 2

#define ACTIVATEUI(A, B) UI::Get()->setUINode(A, B)
#define DEACTIVATEUI UI::Get()->setUINode(nullptr)
#define UPDATEUI UI::Get()->update()

#define ACTIVATEMAINMENUUI(A) UI::Get()->pMainMenu = (CMainMenu*)A; ACTIVATEUI(A, UI_MAINMENU); 

#include "Singleton.h"
#include "cocos2d.h"

class CMainMenu;

USING_NS_CC;

class UI : public TSingleton<UI>
{
public:
	UI(void);
	virtual ~UI(void);

	CMainMenu* pMainMenu;

	void setUINode(Node* _pNode, int _menu);
	void update();
private:
	Node* m_pUINode;
	Node* m_pCommon;
	Node* m_pMenu;
	Node* m_pIngame;

	void createCommonUI();
	void createMainMenuUI();
};

#endif//__UI_H__