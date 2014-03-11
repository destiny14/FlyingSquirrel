#include "UI.h"
#include "MainMenu.h"
#include "MainLayer.h"
#include "CommonMain.h"
#include "Player.h"
#include "Crystal.h"

UI::UI()
{
	active = false;
	m_mainMenuActive = false;

	m_pUINode = Node::create();
	m_pUINode->retain();

	m_pMenu = Node::create();
	m_pMenu->retain();

	m_pIngame = Node::create();
	m_pIngame->retain();

	m_pCommon = Node::create();
	m_pCommon->retain();

	m_pLevelEditor = Node::create();
	m_pLevelEditor->retain();
	m_playerMuni = nullptr;
	m_pGameOver = nullptr;

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
	m_pPlayer = nullptr;
	active = false;
	m_pUINode->removeFromParentAndCleanup(false);
	
	if (_pNode == nullptr) return;

	m_pUINode->removeAllChildrenWithCleanup(false);
	m_pUINode->addChild(m_pCommon);

	m_mainMenuActive = false;

	switch (_menu)
	{
		case UI_MAINMENU:
			createMainMenuUI();
			m_mainMenuActive = true;
			m_pUINode->addChild(m_pMenu);
			break;

		case UI_INGAME:
			createIngameUI();
			m_pUINode->addChild(m_pIngame);
			break;

		case UI_LEVELEDITOR:
			createLevelEditorUI();
			m_pUINode->addChild(m_pLevelEditor);
			break;

		case UI_FILECHOOSER:
			createLevelEditorFilePopup();
			m_pUINode->addChild(m_pLevelEditor);

		case UI_NONE:
		default:
			break;
	}

	_pNode->addChild(m_pUINode, 9999);
	active = true;
}

void UI::createLevelEditorFilePopup()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	

	MenuItemFont* addTextureObject = MenuItemFont::create("choose file", CC_CALLBACK_0(UI::nullCallback, this));
	addTextureObject->setFontNameObj("Segoe UI");
	addTextureObject->setFontSizeObj(34);
	addTextureObject->setPosition(visibleSize.width * 0.5f, visibleSize.height - 30);
	
	MenuItemFont* scrollUpObject = MenuItemFont::create("up", CC_CALLBACK_0(LevelEditor::moveFileSelectUpCallback, pLevelEditor));
	scrollUpObject->setFontNameObj("Segoe UI");
	scrollUpObject->setFontSizeObj(34);
	scrollUpObject->setPosition(visibleSize.width - 50, visibleSize.height - 30);

	MenuItemFont* scrollDownObject = MenuItemFont::create("down", CC_CALLBACK_0(LevelEditor::moveFileSelectDownCallback, pLevelEditor));
	scrollDownObject->setFontNameObj("Segoe UI");
	scrollDownObject->setFontSizeObj(34);
	scrollDownObject->setPosition(visibleSize.width - 50, 30);

	MenuItemImage* scrollBackground = MenuItemImage::create("ui_background.png", "ui_background.png", CC_CALLBACK_0(UI::nullCallback, this));
	scrollBackground->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	scrollBackground->setScale(400, visibleSize.height);

	int paddingTop = 60;
	Vector<MenuItem*> lMenuItems;
	lMenuItems.pushBack(addTextureObject);
	for (string s : getAllFilesInFolder(""))
	{
		MenuItemFont* menuItem = MenuItemFont::create(s, CC_CALLBACK_1(LevelEditor::chooseFileCallback, pLevelEditor, s, levelType));
		menuItem->setFontNameObj("Segoe UI");
		menuItem->setFontSizeObj(24);
		menuItem->setPosition(visibleSize.width * 0.5f, visibleSize.height - paddingTop);
		paddingTop += 30;
		lMenuItems.pushBack(menuItem);
	}
	auto menu = Menu::createWithArray(lMenuItems);
	auto scrollMenu = Menu::create(scrollBackground, scrollDownObject, scrollUpObject,  NULL);
	scrollMenu->retain();
	scrollMenu->setPosition(0, 0);
	scrollMenu->setZOrder(-10);
	menu->retain();
	menu->setPosition(0, 0);
	m_pLevelEditor->addChild(menu);
	m_pLevelEditor->addChild(scrollMenu);
	pLevelEditor->ChooseFileMenu = menu;
	pLevelEditor->ChooseFileNavMenu = scrollMenu;
}

void UI::createLevelEditorUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto labelMenuTitle = LabelTTF::create("Level Editor", "Segoe UI", 12);
	labelMenuTitle->setPosition(35.0f, visibleSize.height - 40.0f);
	m_pLevelEditor->addChild(labelMenuTitle);

	MenuItemImage* sidebarBackground = MenuItemImage::create("ui_background.png", "ui_background.png", CC_CALLBACK_0(UI::nullCallback, this));
	sidebarBackground->setPosition(100.0f, visibleSize.height * 0.5f);
	sidebarBackground->setScale(200, visibleSize.height);
	
	MenuItemFont* addTextureObject = MenuItemFont::create("add texture", CC_CALLBACK_1(LevelEditor::addTextureObjectCallback, pLevelEditor));
	addTextureObject->setFontNameObj("Arial");
	addTextureObject->setFontSizeObj(30);
	addTextureObject->setPosition(80.0f, visibleSize.height - 80.0f);

	MenuItemFont* addGroundObject = MenuItemFont::create("add ground", CC_CALLBACK_1(LevelEditor::addGroundObjectCallback, pLevelEditor));
	addGroundObject->setFontNameObj("Arial");
	addGroundObject->setFontSizeObj(30);
	addGroundObject->setPosition(80.0f, visibleSize.height - 120.0f);

	MenuItemFont* addNutObject = MenuItemFont::create("add nut", CC_CALLBACK_1(LevelEditor::addNutObjectCallback, pLevelEditor));
	addNutObject->setFontNameObj("Arial");
	addNutObject->setFontSizeObj(30);
	addNutObject->setPosition(80.0f, visibleSize.height - 160.0f);

	MenuItemFont* addCrystalObject = MenuItemFont::create("add crystal", CC_CALLBACK_1(LevelEditor::addCrystalObjectCallback, pLevelEditor));
	addCrystalObject->setFontNameObj("Arial");
	addCrystalObject->setFontSizeObj(30);
	addCrystalObject->setPosition(80.0f, visibleSize.height - 200.0f);

	MenuItemFont* addAirObject = MenuItemFont::create("add aircurrent", CC_CALLBACK_1(LevelEditor::addAirObjectCallback, pLevelEditor));
	addAirObject->setFontNameObj("Arial");
	addAirObject->setFontSizeObj(30);
	addAirObject->setPosition(80.0f, visibleSize.height - 240.0f);

	MenuItemFont* changeLayerObject = MenuItemFont::create("mainLayer", CC_CALLBACK_0(LevelEditor::changeLayerCallback, pLevelEditor));
	changeLayerObject->setFontNameObj("Arial");
	changeLayerObject->setFontSizeObj(30);
	changeLayerObject->setPosition(73.0f, visibleSize.height - 280.0f);
	changeLayerObject->setTag(111);

	MenuItemFont* toggleGrid = MenuItemFont::create("snap to grid", CC_CALLBACK_0(LevelEditor::toggleGridCallback, pLevelEditor));
	toggleGrid->setFontNameObj("Arial");
	toggleGrid->setFontSizeObj(30);
	toggleGrid->setPosition(80.0f, visibleSize.height - 320.0f);
	toggleGrid->setTag(112);

	MenuItemFont* toggleSelectionMode = MenuItemFont::create("selection", CC_CALLBACK_0(LevelEditor::toggleSelectionMode, pLevelEditor));
	toggleSelectionMode->setFontNameObj("Arial");
	toggleSelectionMode->setFontSizeObj(30);
	toggleSelectionMode->setPosition(80.0f, visibleSize.height - 360.0f);
	toggleSelectionMode->setTag(113);

	MenuItemFont* saveLevelObject = MenuItemFont::create("save level", CC_CALLBACK_0(LevelEditor::saveLevelCallback, pLevelEditor));
	saveLevelObject->setFontNameObj("Arial");
	saveLevelObject->setFontSizeObj(30);
	saveLevelObject->setPosition(70.0f, visibleSize.height - 400.0f);

	MenuItemFont* mainMenuObject = MenuItemFont::create("Mainmenu", CC_CALLBACK_0(LevelEditor::mainMenuCallback, pLevelEditor));
	mainMenuObject->setFontNameObj("Arial");
	mainMenuObject->setFontSizeObj(30);
	mainMenuObject->setPosition(70.0f, visibleSize.height - 440.0f);
	
	auto menu = Menu::create(addTextureObject, addGroundObject, addNutObject, addCrystalObject, addAirObject, changeLayerObject, toggleSelectionMode, saveLevelObject, toggleGrid, mainMenuObject, NULL);
	auto menuBackground = Menu::create(sidebarBackground, NULL);
	menuBackground->setPosition(0, 0);
	menuBackground->setZOrder(-10);
	menu->setPosition(0, 0);
	m_pLevelEditor->addChild(menu);
	m_pLevelEditor->addChild(menuBackground);
	pLevelEditor->MainMenu = menu;
}

void UI::createCommonUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	char labelVerTxt[30];
	sprintf(labelVerTxt, "%s%s", g_pCommonMain->getAppVersion(), g_pCommonMain->getAppDebug() ? " Dev_Version" : "");
	
	auto labelVer = LabelTTF::create(labelVerTxt, "Arial", 36);
	labelVer->setPosition(Point(3.0f + labelVer->getContentSize().width * 0.5f,
		visibleSize.height - labelVer->getContentSize().height * 0.5f));
	m_pCommon->addChild(labelVer);
}

void UI::createMainMenuUI()
{
	m_pMenu->removeAllChildren();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_timeElapsed = 1;
	m_timeElapsedAll = 0;
	m_animations = 0;
	m_timeToElapse = 1;

	m_pAnimation = Sprite::create();
	m_pAnimation->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_pMenu->addChild(m_pAnimation);

	m_pSpriteFrame2 = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame2->addSpriteFramesWithFile("GUI/menu.plist");
	m_pSpriteBatch = SpriteBatchNode::create("GUI/menu.png");

	for (int i = 0; i < 56; i++)
	{
		filename = String::createWithFormat("skeleton-Reinfahrt%i.png", i);
		frame2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame2);
	}
	m_pStartFrames = Animation::createWithSpriteFrames(frames, 0.0275f);
	m_pStartFrames->retain();
	frames.clear();

	for (int i = 0; i < 51; i++)
	{
		filename = String::createWithFormat("skeleton-NormalMenu%i.png", i);
		frame2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame2);
	}
	m_pIdleFrames = Animation::createWithSpriteFrames(frames, 0.0275f);
	m_pIdleFrames->retain();
	frames.clear();

	for (int i = 0; i < 30; i++)
	{
		filename = String::createWithFormat("skeleton-Rausfahrt%i.png", i);
		frame2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame2);
	}
	m_pEndFrames = Animation::createWithSpriteFrames(frames, 0.0275f);
	m_pEndFrames->retain();
	frames.clear();

	auto startItem = MenuItemFont::create("Spiel starten", CC_CALLBACK_1(CMainMenu::startCallback, pMainMenu));
	startItem->setScale(2.0f);
	startItem->setPosition(Point(
		visibleSize.width * 0.5f,
		visibleSize.height * 0.625f));
	startItem->setOpacity(0);

	auto levelEditor = MenuItemFont::create("Level Editor", CC_CALLBACK_1(CMainMenu::levelEditorCallback, pMainMenu));
	levelEditor->setScale(2.0f);
	levelEditor->setPosition(Point(
		visibleSize.width * 0.5f,
		visibleSize.height * 0.45f));
	levelEditor->setOpacity(0);

	auto closeItem = MenuItemFont::create("Spiel verlassen", CC_CALLBACK_1(CMainMenu::exitCallback , pMainMenu));
	closeItem->setScale(2.0f);
	closeItem->setPosition(Point(
		visibleSize.width * 0.5f,
		visibleSize.height * 0.275f));
	closeItem->setOpacity(0);

	auto menu = Menu::create(startItem, closeItem, levelEditor, NULL);
	menu->setPosition(0.0f, 0.0f);
	m_pMenu->addChild(menu);
}

void UI::createIngameUI()
{
	m_pIngame->removeAllChildren();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//################################################
	m_pPlayer = pHelloWorld->getPlayer();
	lastLife = m_pPlayer->getHealth();
	m_pPlayerLife = new Sprite*[3];

	for (int i = 0; i < 3; ++i)
	{
		std::string str = std::string("GUI/life");
		str.append(std::to_string(i+1));
		str.append(".png");

		m_pPlayerLife[i] = Sprite::create(str);
		m_pPlayerLife[i]->setPosition(
			135.0f + m_pPlayerLife[i]->getContentSize().width * 0.5f,
			95.0f + m_pPlayerLife[i]->getContentSize().height * 0.5f);
		m_pPlayerLife[i]->setVisible((lastLife-1) == i);
		m_pIngame->addChild(m_pPlayerLife[i], 2);
	}

	lastCrystal = CollectibleCrystal::getCrystalCount();
	m_pCrystals = new Sprite*[4];
	for (int i = 0; i < 4; ++i)
	{
		std::string str = std::string("GUI/");
		str.append(std::to_string(i+1));
		str.append(".png");

		m_pCrystals[i] = Sprite::create(str);
		m_pCrystals[i]->setPosition(
			202.0f + m_pCrystals[i]->getContentSize().width * 0.5f,
			42.0f + m_pCrystals[i]->getContentSize().height * 0.5f);
		m_pCrystals[i]->setVisible((lastCrystal - 1) == i);
		m_pIngame->addChild(m_pCrystals[i], 2);
	}

	m_polle = Sprite::create("GUI/holybell.png");
	m_polle->setPosition(270.0f, 66.0f);
	m_polle->setVisible(lastCrystal > 0);

	m_crystal = Sprite::create("GUI/crystall.png");
	m_crystal->setPosition(175.0f, 61.0f);
	m_crystal->setVisible(lastCrystal > 0);

	m_pGameOver = LabelTTF::create("GAME OVER", "Comic Book.ttf", 64);
	m_pGameOver->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_pGameOver->setVisible(false);

	lastMuni = m_pPlayer->getNuts();
	createMuniLabel();

	Sprite* bg = Sprite::create("GUI/bg.png");
	bg->setPosition(
		5 + bg->getContentSize().width * 0.5f,
		5 + bg->getContentSize().height *0.5f);

	m_pIngame->addChild(m_polle, 2);
	m_pIngame->addChild(m_crystal, 2);
	m_pIngame->addChild(bg, 1);

	//################################################

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainLayer::menuCloseCallback, pHelloWorld));
	closeItem->setScale(2.0f);
	closeItem->setPosition(
		visibleSize.width - closeItem->getScaleX() * closeItem->getContentSize().width * 0.5f,
		closeItem->getScaleY() * closeItem->getContentSize().height * 0.5f);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	m_pIngame->addChild(menu, 1);
	m_pIngame->addChild(m_pGameOver, 9999);
}

void UI::update(float dt)
{
	if (m_mainMenuActive)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		m_timeElapsed += dt;
		m_timeElapsedAll += dt;

		if (m_animations == 2)
		{
			m_pAnimation->setPositionX(m_pAnimation->getPositionX() - 16.75f);
		}

		if (m_timeElapsed >= m_timeToElapse)
		{
			m_timeElapsed = 0;
			if (m_animations == 0)
			{
				m_timeElapsed = -2;
				m_animations++;
			}
			else if (m_animations == 1)
			{
				m_timeElapsed = 0.2;
				m_pAnimation->stopAllActions();
				m_pAnimation->setPosition(visibleSize.width, visibleSize.height * 0.5f);
				m_pStartAction = Repeat::create(Animate::create(m_pStartFrames), 1);
				m_pStartAction->setTag(0);
				m_pAnimation->runAction(m_pStartAction);
				m_animations++;
			}
			else if (m_animations == 2)
			{
				m_pAnimation->stopAllActions();
				m_pIdleAction = RepeatForever::create(Animate::create(m_pIdleFrames));
				m_pIdleAction->setTag(1);
				m_pAnimation->runAction(m_pIdleAction);
				m_animations++;
			}

		}
	}

	if (!active) return;

	Point origin = m_pUINode->getParent()->getPosition();
	m_pUINode->setPosition(-origin.x, -origin.y);

	if ((m_pPlayer != nullptr) && (lastLife != m_pPlayer->getHealth()))
	{
		lastLife = m_pPlayer->getHealth();
		for (int i = 0; i < 3; ++i)
			m_pPlayerLife[i]->setVisible((lastLife - 1) == i);
	}

	if ((m_pPlayer != nullptr) && (lastCrystal != CollectibleCrystal::getCrystalCount()))
	{
		lastCrystal = CollectibleCrystal::getCrystalCount();
		m_crystal->setVisible(lastCrystal > 0);
		for (int i = 0; i < 4; ++i)
			m_pCrystals[i]->setVisible((lastCrystal - 1) == i);
	}
	

	if ((m_pPlayer != nullptr) && lastMuni != m_pPlayer->getNuts())
	{
		lastMuni = m_pPlayer->getNuts();
		createMuniLabel();
	}

	if ((m_pPlayer != nullptr) && (m_pGameOver != nullptr))
	{
		static bool dead = false;
		if (!dead && m_pPlayer->getHealth() <= 0)
		{
			m_pGameOver->setVisible(true);
			dead = true;
		}
	}
}

void UI::createMuniLabel()
{
	if (m_playerMuni != nullptr)
		m_playerMuni->removeFromParentAndCleanup(true);

	std::string str = std::string("x");
	str.append(std::to_string(lastMuni));
	m_playerMuni = LabelTTF::create(str, "fonts/Comic Book.ttf", 25);
	m_playerMuni->setColor(Color3B::BLACK);
	m_playerMuni->setPosition(360.0f, 65.0f);
	m_pIngame->addChild(m_playerMuni, 2);
}

void UI::nullCallback() {}

vector<string> UI::getAllFilesInFolder(string folder)
{
	vector<string> names;
	char search_path[200];
	sprintf(search_path, "%s*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(convertCharArrayToLPCWSTR(search_path), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder, delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				//wide char array
				WCHAR* wc = fd.cFileName;

				//convert from wide char to narrow char array
				char chr[260];
				char DefChar = ' ';
				WideCharToMultiByte(CP_ACP, 0, wc, -1, chr, 260, &DefChar, NULL);

				//A std:string  using the char* constructor.
				std::string ss(chr);

				names.push_back(ss);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

wchar_t* UI::convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}