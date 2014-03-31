#include "StoryScene.h"
#include "LevelTestScene.h"
#include "SimpleAudioEngine.h"

Scene* StoryScene::createStoryScene()
{
	Scene* scene = Scene::create();
	auto layer = StoryScene::create();
	scene->addChild(layer);
	return scene;
}

bool StoryScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = EGLView::getInstance()->getVisibleSize();
	visibleSize = Director::getInstance()->getVisibleSize();
	m_parallaxLayer = ParallaxLayer::create();
	m_pCam = new GameCamera(this);
	m_pSprites = new Sprite*[8];
	for (int i = 0; i < 8; ++i)
	{
		std::string str = std::string("par");
		str.append(std::to_string(i + 1));
		str.append(".png");

		m_pSprites[i] = Sprite::create(str);
		m_pSprites[i]->retain();
		m_pSprites[i]->setPosition(
			Director::getInstance()->getVisibleSize().width * 0.5f,
			Director::getInstance()->getVisibleSize().height * 0.5f);
		m_pSprites[i]->setOpacity(0);
		addChild(m_pSprites[i]);
	}
	m_pSprites[0]->setOpacity(255);
	
	m_oldWiseSprite = Sprite::create("raum_weiser.png");
	m_oldWiseSprite->setPosition(20 + Director::getInstance()->getVisibleSize().width * 0.5f,
		Director::getInstance()->getVisibleSize().height * 0.5f + 50);
	m_oldWiseSprite->setOpacity(0);
	m_oldWiseSprite->retain();

	m_oldWiseTextbox1 = Sprite::create("wise_textbox.png");
	m_oldWiseTextbox1->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f,
		Director::getInstance()->getVisibleSize().height * 0.5f);
	m_oldWiseTextbox1->setOpacity(0);
	m_oldWiseTextbox1->retain();
	m_oldWiseTextbox1->setZOrder(4);

	m_oldWiseTextbox2 = Sprite::create("wise_textbox2.png");
	m_oldWiseTextbox2->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f,
		Director::getInstance()->getVisibleSize().height * 0.5f);
	m_oldWiseTextbox2->setOpacity(0);
	m_oldWiseTextbox2->retain();
	m_oldWiseTextbox2->setZOrder(4);

	m_platform = Sprite::create("flightlevel/platformkomplett.png");
	m_platform->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f - 1500,
		Director::getInstance()->getVisibleSize().height * 0.5f + 0.3f);
	m_platform->retain();
	m_platform->setScale(0.8f);
	m_platform->setZOrder(4);

	m_moveNode = Node::create();
	m_moveNode->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f,
		Director::getInstance()->getVisibleSize().height * 0.5f);
	m_moveNode->retain();

	m_pCam->setFollowTarget(m_moveNode);
	m_pCam->setBoundingRect(Rect(-10000.0f, -20000.0f, 24000.0f, 40000.0f));

	//this->addChild(n);

	Point paraPos = Point(1000.0f, 500.0f);/*
	Sprite* m_test = Sprite::create("flbg1.png");
	m_test->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f,
		Director::getInstance()->getVisibleSize().height * 0.5f);
	addChild(m_test);*/
	
	m_parallaxLayer->addParallaxElement(Sprite::create("flbg1.png"), paraPos, Point(0.3f, 0.1f), 5);
	m_parallaxLayer->addParallaxElement(Sprite::create("flbg2.png"), paraPos, Point(0.03f, 0.01f), 4);
	m_parallaxLayer->addParallaxElement(Sprite::create("flbg3.png"), paraPos, Point(0.003f, 0.001f), 3);
	m_parallaxLayer->addParallaxElement(Sprite::create("flbg4.png"), Point(1000.0f, 600.0f), Point(0.0003f, 0.0001f), 2);
	m_parallaxLayer->addParallaxElement(Sprite::create("flbg5.png"), paraPos /*Point(1000.0f, 800.0f)*/, Point(0.00003f, 0.00001f), 1);
	
	m_parallaxLayer->setOpacity(0);
	//m_parallaxLayer->setScale(2.0f);
	this->addChild(m_parallaxLayer, -9999);

	m_pSawyer = Sprite::create("sawyer.png");
	m_pSawyer->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f - 1400,
		Director::getInstance()->getVisibleSize().height * 0.5f + 50);
	m_pSawyer->setZOrder(6);

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("sawyer.plist");
	m_pSpriteBatch = SpriteBatchNode::create("sawyer.png");

	////////////////////////
	// Stehen - Animation // // 0
	////////////////////////
	for (int i = 0; i < 31; i++)
	{
		filename = String::createWithFormat("skeleton-Stand%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pStandFrames = Animation::createWithSpriteFrames(frames, 0.065f);
	m_pStandAction = RepeatForever::create(Animate::create(m_pStandFrames));
	m_pStandAction->setTag(0);
	m_pStandFrames->retain();
	frames.clear();

	//////////////////////////
	// Springen - Animation // // 2
	//////////////////////////
	for (int i = 0; i < 43; i++)
	{
		filename = String::createWithFormat("skeleton-Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pJumpFrames = Animation::createWithSpriteFrames(frames, 0.01f);
	m_pJumpFrames->retain();
	frames.clear();

	//////////////////////
	// Flug - Animation // // 3
	//////////////////////
	for (int i = 0; i < 21; i++)
	{
		filename = String::createWithFormat("skeleton-Flug%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pFlightFrames = Animation::createWithSpriteFrames(frames, 0.035f);
	m_pFlightFrames->retain();
	frames.clear();

	m_pSawyer->stopAllActions();
	m_pStandAction = RepeatForever::create(Animate::create(m_pStandFrames));
	m_pStandAction->setTag(0);
	m_pSawyer->runAction(m_pStandAction);


	//InputManager m_pInput = new InputManager();
	//m_pPlayer = Player::create("sawyer.png", dynamic_cast<MainLayer*>(this), m_pInput);
	//m_pPlayer->setPosition(getPlayerSpawner()->getSpawnPosition());
	//this->addChild(m_pPlayer->getSprite(), 1);

	addChild(m_oldWiseSprite);
	addChild(m_oldWiseTextbox1);
	addChild(m_oldWiseTextbox2);
	addChild(m_platform);
	addChild(m_moveNode);
	addChild(m_pSawyer);
	m_timeElapsed = 0;
	m_timeToElapse = 6;
	m_page = 1;
	
	m_pInput = new InputManager(this);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_ESCAPE;
	m_pSkip = m_pInput->createKeyboardAction(&code, 1, "skip");
	
	this->scheduleUpdate();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/music/B01.wav", true);
	return true;
}

void StoryScene::update(float dt)
{
	m_pCam->update(dt);
	m_timeElapsed += dt;
	m_pInput->update();
	if (m_pSkip->isPressed())
	{
		Director::getInstance()->replaceScene(LevelTestScene::createScene());
	}
	if (m_timeElapsed >= m_timeToElapse)
	{
		m_timeElapsed = 0;
		if (m_page > 0 && m_page <= 8)
		{
			auto fOutAction = FadeOut::create(1);
			m_pSprites[m_page - 1]->runAction(fOutAction);
		}
		if (m_page < 8)
		{
			auto fInAction = FadeIn::create(1);
			m_pSprites[m_page]->runAction(fInAction);
			m_page++;
		}
		else if (m_page == 8)
		{

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/music/i.wav", true);
			auto inAction = FadeIn::create(1);
			m_oldWiseSprite->runAction(inAction);
			m_timeToElapse = 2;
			++m_page;
		}
		else if (m_page == 9)
		{
			auto inAction = FadeIn::create(1);
			m_oldWiseTextbox1->runAction(inAction);
			++m_page;
			m_timeToElapse = 10;
		}
		else if (m_page == 10)
		{
			auto fadeOut = FadeOut::create(1);
			m_oldWiseTextbox1->runAction(fadeOut);
			auto inAction = FadeIn::create(1);
			m_oldWiseTextbox2->runAction(inAction);
			++m_page;
		}
		else if (m_page == 11)
		{
			auto fadeOut = FadeOut::create(1);
			auto fadeOut2 = FadeOut::create(1);
			m_oldWiseTextbox2->runAction(fadeOut);
			m_oldWiseSprite->runAction(fadeOut2);
			m_timeToElapse = 1;
			++m_page;
		}
		else if (m_page == 12)
		{
			auto mb = MoveBy::create(2, Point(-1200, 0));
			m_moveNode->runAction(mb);
			m_timeToElapse = 4;
			++m_page;
		}
		else if (m_page == 13)
		{
			auto mb = MoveBy::create(0.5, Point(5, 100));
			m_pSawyer->runAction(mb);
			m_pJumpAction = Repeat::create(Animate::create(m_pJumpFrames), 1);
			m_pJumpAction->setTag(2);
			m_pSawyer->runAction(m_pJumpAction);
			m_timeToElapse = 0.5;
			++m_page;
			/*m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			m_pSawyer->runAction(m_pFlightAction);*/
		}
		else if (m_page == 14)
		{
			m_pSawyer->stopActionByTag(0);
			m_pSawyer->stopActionByTag(2);
			auto mb = MoveBy::create(5, Point(4200, -200));
			auto mb2 = MoveBy::create(5, Point(3000, -100));
			m_pSawyer->runAction(mb);
			m_moveNode->runAction(mb2);
			m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			m_pSawyer->runAction(m_pFlightAction);
			m_timeToElapse = 4.8;
			++m_page;
		}
		else if (m_page == 15)
		{
			auto sc = TransitionFade::create(1.0, LevelTestScene::createScene());
			Director::getInstance()->replaceScene(sc);
			++m_page;
		}
	}
}

void StoryScene::draw()
{

}