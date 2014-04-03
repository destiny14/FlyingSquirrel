#include "CreditScene.h"
#include "Input.h"
#include "MainMenu.h"
#include <list>

Scene* CreditScene::createScene() {
	Scene* scene = Scene::create();
	auto layer = CreditScene::create();
	scene->addChild(layer);
	return scene;
}

bool CreditScene::init() {
	if (!Layer::init()) return false;

	textSpeed = 75.0f;
	contentNode = Node::create();
	enemies = Node::create();

	//create input
	input = new InputManager(this);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_SPACE;
	speed = input->createKeyboardAction(&code, 1, "Speed");
	
	//Enemies
	Vector<SpriteFrame*> frames;
	auto mantis = Sprite::create("mantis.png");

	auto m_pSpriteFrame = SpriteFrameCache::getInstance();
	m_pSpriteFrame->addSpriteFramesWithFile("mantis2.plist");
	auto m_pSpriteBatch = SpriteBatchNode::create("mantis2.png");
	
	for (int i = 0; i < 35; i++)
	{
		auto m_pSpriteString = String::createWithFormat("Mantis_Run(%i).png", i);
		auto m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	auto m_pRunFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	auto m_pRunAction = RepeatForever::create(Animate::create(m_pRunFrames));
	m_pRunAction->setTag(1);
	mantis->runAction(m_pRunAction);

	enemies->addChild(mantis);
	mantis->setPosition(Point(1450.0f, 75.0f));
	mantis->setScale(0.33f);

	m_pRunFrames->retain();
	frames.clear();

	//Content
	std::list<Node*> content = std::list<Node*>();

	//Create the content
	content.push_front(LabelTTF::create("FlyingSquirrel", "fonts/Comic Book.ttf", 100.0f));
	content.push_front(LabelTTF::create("", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Artists", "fonts/Comic Book.ttf", 75.0f));
	content.push_front(LabelTTF::create("Marina Hahn", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Ingo Hoffmann", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(Sprite::create("credits1.png"));
	content.push_front(Sprite::create("credits2.png"));
	content.push_front(LabelTTF::create("Vladimir Obuchoff", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Ruth Erdeljan", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Reserved", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Reserved", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Coder", "fonts/Comic Book.ttf", 75.0f));
	content.push_front(LabelTTF::create("Marco Stambor", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Sebastian Engfer", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Patrick Fahlbusch", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(LabelTTF::create("Kevin Schwarz", "fonts/Comic Book.ttf", 50.0f));
	content.push_front(Sprite::create("sae_logo.png"));

	//Add all Labels to the text node

	float pos = 0.0f;
	float lineSize = 50.0f;

	while (!content.empty()) {
		Node* node = content.front();
		content.remove(node);
		if (node == nullptr) continue;

		contentNode->addChild(node);
		node->setPositionY(pos);

		pos += node->getContentSize().height + lineSize;
	}

	//Add the text node to the scene
	addChild(enemies);
	addChild(contentNode);
	contentNode->setPositionX(Director::getInstance()->getVisibleSize().width / 2.0f);
	contentNode->setPositionY(pos * -0.7f - Director::getInstance()->getVisibleSize().height);

	size = pos * 1.2f + Director::getInstance()->getVisibleSize().height;

	scheduleUpdate();

	return true;
}

void CreditScene::update(float _dt) {
	input->update();

	if (speed->wasPressed())
		textSpeed *= 10.0f;
	if (speed->wasReleased())
		textSpeed /= 10.0f;

	float move = textSpeed * _dt;
	contentNode->setPositionY(contentNode->getPositionY() + move);
	size -= move;

	if (enemies != nullptr && size <= 1000.0f)
	{
		enemies->removeFromParentAndCleanup(true);
		enemies = nullptr;
	}
		
	if (size <= 0)
		Director::getInstance()->replaceScene(CMainMenu::createMainMenuScene());
}