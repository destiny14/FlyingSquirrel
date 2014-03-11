#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "cocos2d.h"
#include "InputManager.h"

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
	Sprite* m_pCocosLogo;
	Sprite* m_pBlack;
	float m_timeElapsed;
	float m_timeToElapse;
	int m_page;

	InputManager* m_pInput;
	InputAction* m_pSkip;

	Sprite* m_pIntro;

	Animation* m_pIntroFrames;
	Action* m_pIntroAction;

	Vector<SpriteFrame*> frames;
	String* filename;
	SpriteFrame* frame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;
};

#endif // !__INTROSCENE_H__
