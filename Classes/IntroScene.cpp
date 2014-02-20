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

	m_timeElapsed = 0;
	m_page = 0;
	m_timeToElapse = 3;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_saeLogo = Sprite::create("sae_logo.png");
	m_saeLogo->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	m_saeLogo->setOpacity(0);
	addChild(m_saeLogo);
	this->scheduleUpdate();
	return true;
}

void IntroScene::update(float dt)
{
	m_timeElapsed += dt;
	if (m_timeElapsed >= m_timeToElapse)
	{
		m_timeElapsed = 0;
		if (m_page == 0)
		{
			FadeIn* fInAction = FadeIn::create(0.5);
			m_saeLogo->runAction(fInAction);
			m_page++;
		}
		else
		{
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