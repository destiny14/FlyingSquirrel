#ifndef __UI_H__
#define __UI_H__

#include "cocos2d.h"

USING_NS_CC;

class UI
{
public:
	UI(Node* _pSrcNode, char* _uiFileLocation);
	virtual ~UI(void);

	void freeResources();
	void reloadUI();
	void enableUI();
	void disableUI();
	bool isEnabled() { return m_enabled; }
private:
	Node* m_pUINode;
	Node* m_pNode;
	char* m_uiFileLoc;
	bool m_enabled;
	ScriptEngineProtocol* m_pEngine;

	void loadResources();
};

#endif __UI_H__