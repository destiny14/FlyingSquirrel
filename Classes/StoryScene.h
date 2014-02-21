#ifndef _STORYSCENE_H_
#define _STORYSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class StoryScene : public Layer
{
public:
	static Scene* createStoryScene();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();

	CREATE_FUNC(StoryScene);
private:
	Sprite** m_pSprites;
	Sprite* m_oldWiseSprite;
	float m_timeElapsed;
	float m_timeToElapse;
	int m_page;
};

#endif // !_STORYSCENE_H_
