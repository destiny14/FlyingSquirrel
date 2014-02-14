#include "UI.h"
#include "MainMenu.h"
#include "CommonMain.h"

UI::UI()
{
	active = false;

	m_pUINode = Node::create();
	m_pUINode->retain();

	m_pMenu = Node::create();
	m_pMenu->retain();

	m_pIngame = Node::create();
	m_pIngame->retain();

	m_pCommon = Node::create();
	m_pCommon->retain();

	createCommonUI();
}

UI::~UI()
{
	setUINode(nullptr, UI_NONE);

	m_pUINode->release();
	m_pMenu->release();
	m_pIngame->release();
	m_pCommon->release();
}

void UI::setUINode(Node* _pNode, int _menu)
{
	active = false;
	m_pUINode->removeFromParentAndCleanup(false);
	
	if (_pNode == nullptr) return;

	m_pUINode->removeAllChildrenWithCleanup(false);
	m_pUINode->addChild(m_pCommon);

	switch (_menu)
	{
		case UI_MAINMENU:
			createMainMenuUI();
			m_pUINode->addChild(m_pMenu);
			break;

		case UI_INGAME:
			m_pUINode->addChild(m_pIngame);
			break;

		case UI_NONE:
		default:
			break;
	}

	_pNode->addChild(m_pUINode, 1);
	active = true;
}

void UI::createCommonUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	char labelVerTxt[30];
	sprintf(labelVerTxt, "%s%s", g_pCommonMain->getAppVersion(), g_pCommonMain->getAppDebug() ? " Dev_Version" : "");
	
	auto labelVer = LabelTTF::create(labelVerTxt, "Arial", 18);
	labelVer->setPosition(Point(3.0f + labelVer->getContentSize().width * 0.5f,
		visibleSize.height - labelVer->getContentSize().height * 0.5f));
	m_pCommon->addChild(labelVer);
}

void UI::createMainMenuUI()
{
	m_pMenu->removeAllChildren();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CMainMenu::exitCallback, pMainMenu));
	closeItem->setPosition(Point(
		visibleSize.width - closeItem->getContentSize().width * 0.5f,
		closeItem->getContentSize().height * 0.5f));

	auto startItem = MenuItemFont::create("Start (Leertaste)", CC_CALLBACK_1(CMainMenu::startCallback, pMainMenu));
	startItem->setPosition(Point(
		visibleSize.width * 0.5f,
		visibleSize.height * 0.5f));

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->setPosition(0.0f, 0.0f);
	m_pMenu->addChild(menu);
}

void UI::update()
{
	if (!active) return;

	Point origin = m_pUINode->getParent()->getPosition();
	m_pUINode->setPosition(-origin.x, -origin.y);
}