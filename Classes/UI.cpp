#include "UI.h"

UI::UI()
{
	m_pUINode = Menu::create();
	createUI();
}

UI::~UI()
{
	setUINode(nullptr);
	m_pUINode->release();
}

void UI::setUINode(Node* _pNode)
{
	m_pUINode->removeFromParent();

	if (_pNode == nullptr) return;

	_pNode->addChild(m_pUINode);
}

void UI::createUI()
{
	auto testLabel = LabelTTF::create("UI Test", "Arial", 12);

	m_pUINode->addChild(testLabel);
}