#ifndef __UI_H__
#define __UI_H__

#include "cocos2d.h"

USING_NS_CC;

class UIData
{
public:
	UIData(char* _uiLocation);
	~UIData(void);

	std::string* uiLoc;
	std::string* listLoc;
	std::string* scriptLoc;

	Node* pUINode;
	ScriptEngineProtocol* pEngine;
};

class UI
{
public:
	UI(Node* _pSrcNode, char* _uiLocation);
	virtual ~UI(void);

	void freeResources();
	void reloadUI();
	void enableUI();
	void disableUI();
	bool isEnabled() { return m_enabled; }
private:
	char* m_uiLoc;
	Node* m_pNode;
	bool m_enabled;
	UIData* m_pData;

	void loadResources();
};
#endif __UI_H__