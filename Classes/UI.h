#ifndef __UI_H__
#define __UI_H__

#define ACTIVATEUI(A) UI::Get()->setUINode(A);
#define DEACTIVATEUI UI::Get()->setUINode(nullptr);

#include "Singleton.h"
#include "cocos2d.h"

USING_NS_CC;

class UI : public TSingleton<UI>
{
public:
	void setUINode(Node* _pNode);

protected:
	UI(void);
	virtual ~UI(void);

private:
	Menu* m_pUINode;

	void createUI();
};

#endif//__UI_H__