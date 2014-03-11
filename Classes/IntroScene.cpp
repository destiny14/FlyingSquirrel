#include "IntroScene.h"
#include "MainMenu.h"

Scene* IntroScene::createScene()
{
	Scene* scene = Scene::create();
	auto layer = IntroScene::create();
	scene->addChild(layer);
	return scene;
}

bool IntroScene::init()
{
	if (!Layer::init())
		return false;

	glClearColor(255, 255, 255, 255);

	m_timeElapsed = 5;
	m_page = 0;
	m_timeToElapse = 5;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_saeLogo = Sprite::create("sae_logo.png");
	m_saeLogo->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_saeLogo->setOpacity(0);
	addChild(m_saeLogo);

	m_pCocosLogo = Sprite::create("cocos.png");
	m_pCocosLogo->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_pCocosLogo->setOpacity(0);
	addChild(m_pCocosLogo);

	m_pBlack = Sprite::create("black.png");
	m_pBlack->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_pBlack->setOpacity(0);
	addChild(m_pBlack);

	m_pIntro = Sprite::create("intro.png");
	m_pIntro->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_pIntro->setScale(2);
	addChild(m_pIntro);
	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("intro.plist");
	m_pSpriteBatch = SpriteBatchNode::create("intro.png");

	m_pInput = new InputManager(this);
	EventKeyboard::KeyCode code = EventKeyboard::KeyCode::KEY_ESCAPE;
	m_pSkip = m_pInput->createKeyboardAction(&code, 1, "skip");

	for (int i = 0; i < 60; i++)
	{
		filename = String::createWithFormat("Intro%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pIntroFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pIntroFrames->retain();
	frames.clear();

	this->scheduleUpdate();

	return true;
}

void IntroScene::update(float dt)
{
	m_timeElapsed += dt;
	m_pInput->update();
	if (m_pSkip->isPressed())
	{
		glClearColor(0, 0, 0, 255);

		auto menu = CMainMenu::createMainMenuScene();
		Director::getInstance()->replaceScene(menu);
		Director::getInstance()->setDepthTest(true);
		/*
		TransitionFade* fade = TransitionFade::create(1, menu);
		Director::getInstance()->replaceScene(fade);
		*/
	}
	if (m_timeElapsed >= m_timeToElapse)
	{
		m_timeElapsed = 0;
		if (m_page == 0)
		{
			FadeIn* fInAction = FadeIn::create(0.5);
			m_saeLogo->runAction(fInAction);
			m_page++;
		}
		else if (m_page == 1)
		{
			m_timeElapsed = 4.0f;
			FadeOut* fOutAction = FadeOut::create(0.25);
			m_saeLogo->runAction(fOutAction);
			m_page++;
		}
		else if (m_page == 2)
		{
			m_timeElapsed = 2.5f;
			FadeIn* fInAction2 = FadeIn::create(0.5);
			m_pCocosLogo->runAction(fInAction2);
			m_page++;
		}
		else if (m_page == 3)
		{
			m_timeElapsed = 4.0f;
			FadeOut* fOutAction2 = FadeOut::create(0.25);
			m_pCocosLogo->runAction(fOutAction2);
			m_page++;
		}
		else if (m_page == 4)
		{
			m_timeElapsed = 3.0f;
			FadeIn* fInAction3 = FadeIn::create(2.0);
			m_pBlack->runAction(fInAction3);
			m_page++;
		}
		else if (m_page == 5)
		{
		
			m_pIntroAction = Repeat::create(Animate::create(m_pIntroFrames), 1);
			m_pIntroAction->setTag(0);
			m_pIntro->runAction(m_pIntroAction);
			m_page++;
		}
		else
		{
			glClearColor(0, 0, 0, 255);

			auto menu = CMainMenu::createMainMenuScene();
			Director::getInstance()->setDepthTest(true);

			TransitionFade* fade = TransitionFade::create(1, menu);
			Director::getInstance()->replaceScene(fade);
		}
	}
}

void IntroScene::draw()
{

}