#include "UI.h"

UI::UI(Node* _pSrcNode, char* _uiLocation)
{
	m_pData = nullptr;
	m_pNode = _pSrcNode;
	m_enabled = false;
	m_uiLoc = _uiLocation;
}

UI::~UI()
{
	freeResources();
}

void UI::freeResources()
{
	if (m_pData == nullptr) return;

	//Node aufraeumen
	m_pData->pUINode->removeFromParentAndCleanup(true);
	m_pData->pUINode->release();
	m_pData->pUINode = nullptr;

	//Engine aufraeumen
	//delete m_pEngine;

	delete m_pData;
	m_pData = nullptr;
}

void UI::loadResources()
{
	if (m_pData != nullptr) return;

	m_pData = new UIData(m_uiLoc);

	//Node generieren
	m_pData->pUINode = Node::create();
	//Engine holen
	m_pData->pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
	//Script ausfuehren
	m_pData->pEngine->executeScriptFile((const char*)(m_pData->scriptLoc));
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
	if (m_pData == nullptr) loadResources();
	
	m_pNode->addChild(m_pData->pUINode);
	m_enabled = true;
}

void UI::disableUI()
{
	if (!m_enabled) return;
	if (m_pData == nullptr) return;

	m_pData->pUINode->removeFromParent();
	m_enabled = false;
}

UIData::UIData(char* _uiLocation)
{
	uiLoc = new std::string(_uiLocation);

	//Position der pList
	listLoc = new std::string(_uiLocation);
	listLoc->append("/atlas.plist");

	//Position des Scripts
	scriptLoc = new std::string(_uiLocation);
	scriptLoc->append("/ui.lua");

	//Nicht verwaltete Variablen nullen
	pUINode = nullptr;
	pEngine = nullptr;
}

UIData::~UIData()
{
	delete uiLoc;
	delete listLoc;
	delete scriptLoc;

	//Nicht verwaltete Variablen nullen
	pUINode = nullptr;
	pEngine = nullptr;
}