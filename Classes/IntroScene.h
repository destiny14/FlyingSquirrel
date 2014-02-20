#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class IntroScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();

	CREATE_FUNC(IntroScene);
private:
	Sprite* m_saeLogo;
	float m_timeElapsed;
	float m_timeToElapse;
};

#endif // !__INTROSCENE_H__
