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

	m_pLevelEditor = Node::create();
	m_pLevelEditor->retain();

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

	_pNode->addChild(m_pUINode, 1);
	active = true;
}

void UI::createLevelEditorFilePopup()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	

	MenuItemFont* addTextureObject = MenuItemFont::create("choose file", CC_CALLBACK_0(UI::nullCallback, this));
	addTextureObject->setFontNameObj("Segoe UI");
	addTextureObject->setFontSizeObj(24);
	addTextureObject->setPosition(visibleSize.width * 0.5f, visibleSize.height - 30);
	
	MenuItemFont* scrollUpObject = MenuItemFont::create("up", CC_CALLBACK_0(LevelEditor::moveFileSelectUpCallback, pLevelEditor));
	scrollUpObject->setFontNameObj("Segoe UI");
	scrollUpObject->setFontSizeObj(24);
	scrollUpObject->setPosition(visibleSize.width - 40, visibleSize.height - 30);

	MenuItemFont* scrollDownObject = MenuItemFont::create("down", CC_CALLBACK_0(LevelEditor::moveFileSelectDownCallback, pLevelEditor));
	scrollDownObject->setFontNameObj("Segoe UI");
	scrollDownObject->setFontSizeObj(24);
	scrollDownObject->setPosition(visibleSize.width - 40, 30);

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
		menuItem->setFontSizeObj(14);
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
	labelMenuTitle->setPosition(35.0f, visibleSize.height - 30.0f);
	m_pLevelEditor->addChild(labelMenuTitle);

	MenuItemFont* addTextureObject = MenuItemFont::create("add texture", CC_CALLBACK_1(LevelEditor::addTextureObjectCallback, pLevelEditor));
	addTextureObject->setFontNameObj("Segoe UI");
	addTextureObject->setFontSizeObj(14);
	addTextureObject->setPosition(40.0f, visibleSize.height - 60.0f);

	MenuItemFont* addGroundObject = MenuItemFont::create("add ground", CC_CALLBACK_1(LevelEditor::addGroundObjectCallback, pLevelEditor));
	addGroundObject->setFontNameObj("Segoe UI");
	addGroundObject->setFontSizeObj(14);
	addGroundObject->setPosition(40.0f, visibleSize.height - 90.0f);

	MenuItemFont* changeLayerObject = MenuItemFont::create("mainLayer", CC_CALLBACK_0(LevelEditor::changeLayerCallback, pLevelEditor));
	changeLayerObject->setFontNameObj("Segoe UI");
	changeLayerObject->setFontSizeObj(14);
	changeLayerObject->setPosition(40.0f, visibleSize.height - 120.0f);
	changeLayerObject->setTag(111);

	MenuItemFont* saveLevelObject = MenuItemFont::create("save level", CC_CALLBACK_0(LevelEditor::saveLevelCallback, pLevelEditor));
	saveLevelObject->setFontNameObj("Segoe UI");
	saveLevelObject->setFontSizeObj(14);
	saveLevelObject->setPosition(40.0f, visibleSize.height - 150.0f);
	
	auto menu = Menu::create(addTextureObject, addGroundObject, changeLayerObject, saveLevelObject, NULL);
	menu->setPosition(0, 0);
	m_pLevelEditor->addChild(menu);
	pLevelEditor->MainMenu = menu;
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

	auto levelEditor = MenuItemFont::create("Level Editor", CC_CALLBACK_1(CMainMenu::levelEditorCallback, pMainMenu));
	levelEditor->setPosition(Point(
		visibleSize.width * 0.5f,
		visibleSize.height * 0.5f - 50));

	auto menu = Menu::create(startItem, closeItem, levelEditor, NULL);
	menu->setPosition(0.0f, 0.0f);
	m_pMenu->addChild(menu);
}

void UI::update()
{
	if (!active) return;

	Point origin = m_pUINode->getParent()->getPosition();
	m_pUINode->setPosition(-origin.x, -origin.y);
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