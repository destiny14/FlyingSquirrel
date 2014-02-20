#include "StoryScene.h"

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
	addChild(m_oldWiseSprite);
	m_timeElapsed = 0;
	m_timeToElapse = 6;
	m_page = 1;
	this->scheduleUpdate();
	return true;
}

void StoryScene::update(float dt)
{
	m_timeElapsed += dt;
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
			auto inAction = FadeIn::create(1);
			m_oldWiseSprite->runAction(inAction);
			m_page++;
		}
	}
}

void StoryScene::draw()
{

}