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
	code = EventKeyboard::KeyCode::KEY_0;
	colorIt = input->createKeyboardAction(&code, 1, "ColorIt");
	
	//Enemies
	Vector<SpriteFrame*> frames;
	auto mantis = Sprite::create("Resources/animations/mantis.png");

	auto m_pSpriteFrame = SpriteFrameCache::getInstance();
	m_pSpriteFrame->addSpriteFramesWithFile("Resources/animations/mantis.plist");
	auto m_pSpriteBatch = SpriteBatchNode::create("Resources/animations/mantis.png");
	
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

	auto hamster = Sprite::create("Resources/animations/hamster.png");

	m_pSpriteFrame->addSpriteFramesWithFile("Resources/animations/hamster.plist");
	m_pSpriteBatch = SpriteBatchNode::create("Resources/animations/hamster.png");

	for (int i = 1; i <= 111; i++)
	{
		auto m_pSpriteString = String::createWithFormat("Essen (%i).png", i);
		auto m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	auto m_pRunFrames2 = Animation::createWithSpriteFrames(frames, 0.015f);
	auto m_pRunAction2 = RepeatForever::create(Animate::create(m_pRunFrames2));
	m_pRunAction2->setTag(1);
	hamster->runAction(m_pRunAction2);

	enemies->addChild(hamster);
	hamster->setPosition(Point(50.0f, 75.0f));
	hamster->setScale(0.33f);

	m_pRunFrames2->retain();
	frames.clear();

	//Content
	std::list<Node*> content = std::list<Node*>();
	std::string font = "Resources/fonts/Comic Book.ttf";
	//Create the content
	content.push_front(LabelTTF::create("Flying Squirrel", font, 100.0f));
	content.push_front(LabelTTF::create("", font, 50.0f));
	content.push_front(LabelTTF::create("Artists", font, 75.0f));
	content.push_front(LabelTTF::create("Marina Hahn", font, 50.0f));
	content.push_front(LabelTTF::create("Ingo Hoffmann", font, 50.0f));
	content.push_front(Sprite::create("Resources/pictures/generic/credits1.png"));
	content.push_front(Sprite::create("Resources/pictures/generic/credits2.png"));
	content.push_front(LabelTTF::create("Vladimir Obuchoff", font, 50.0f));
	content.push_front(LabelTTF::create("Ruth Erdeljan", font, 50.0f));
	content.push_front(LabelTTF::create("Ruth Bittlinsky", font, 50.0f));
	content.push_front(LabelTTF::create("", font, 50.0f));
	content.push_front(LabelTTF::create("Audio", font, 75.0f));
	content.push_front(LabelTTF::create("Bastian Hoffman", font, 50.0f));
	content.push_front(LabelTTF::create("", font, 50.0f));
	content.push_front(LabelTTF::create("Coder", font, 75.0f));
	content.push_front(LabelTTF::create("Marco Stambor", font, 50.0f));
	content.push_front(LabelTTF::create("Sebastian Engfer", font, 50.0f));
	content.push_front(LabelTTF::create("Patrick Fahlbusch", font, 50.0f));
	content.push_front(LabelTTF::create("Kevin Schwarz", font, 50.0f));
	content.push_front(Sprite::create("Resources/pictures/generic/sae_logo.png"));

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

	if (enemies != nullptr && size <= 1300.0f)
	{
		enemies->removeFromParentAndCleanup(true);
		enemies = nullptr;
	}
		
	if (size <= 0)
		Director::getInstance()->replaceScene(CMainMenu::createMainMenuScene());

	if (colorIt->isPressed())
	{
		static int e = 1;
		static float prog = 0.0f;
		static int cLength = 4;
		static Color4F colors[4] = { Color4F::BLACK, Color4F::ORANGE, Color4F::GREEN, Color4F::ORANGE };
		static Color4F start = colors[0];
		static Color4F end = colors[1];

		prog += _dt * 0.5f;

		if (prog > 1.0f)
		{
			prog = 0.0f;
			start = end;
			++e;
			if (e == cLength)
				e = 0;
			end = colors[e];
		}

		Color4F color = Color4F((start.r + (end.r - start.r) * prog), (start.g + (end.g - start.g) * prog), (start.b + (end.b - start.b) * prog), 255.0f);

		glClearColor(color.r, color.g, color.b, color.a);
	}
	if (colorIt->wasReleased())
	{
		glClearColor(0, 0, 0, 255);
	}
}