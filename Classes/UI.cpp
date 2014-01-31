#include "UI.h"

UI::UI(Node* _pSrcNode, char* _uiFileLoc)
{
	m_pNode = _pSrcNode;
	m_uiFileLoc = _uiFileLoc;
	m_enabled = false;
	m_pEngine = nullptr;
	m_pUINode = nullptr;
}

UI::~UI()
{

}

void UI::freeResources()
{
	if (m_pEngine == nullptr) return;

	//Node aufraeumen
	m_pUINode->removeFromParentAndCleanup(true);
	m_pUINode->release();
	m_pUINode = nullptr;

	//Engine aufraeumen
	//delete m_pEngine;
	m_pEngine = nullptr;
}

void UI::loadResources()
{
	if (m_pEngine != nullptr) return;

	//Node generieren
	m_pUINode = Node::create();
	m_pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
	//m_pEngine->executeScriptFile(m_uiFileLoc);
}

void UI::reloadUI()
{
	disableUI();
	freeResources();
	enableUI();
}

void UI::enableUI()
{
	if (m_enabled) return;
	if (m_pEngine == nullptr) loadResources();
	
	m_pNode->addChild(m_pUINode);
	m_enabled = true;
}

void UI::disableUI()
{
	if (!m_enabled) return;
	if (m_pEngine == nullptr) return;

	m_pUINode->removeFromParent();
	m_enabled = false;
}