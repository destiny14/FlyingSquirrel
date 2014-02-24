#ifndef _STORYSCENE_H_
#define _STORYSCENE_H_

#include "cocos2d.h"
#include "ParallaxLayer.h"
#include "GameCamera.h"
#include "Player.h"

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
	Animation* m_pStandFrames;
	Animation* m_pFlightFrames;
	Animation* m_pJumpFrames;


	Action* m_pStandAction;
	Action* m_pFlightAction;
	Action* m_pJumpAction;

	Vector<SpriteFrame*> frames;
	String* filename;
	SpriteFrame* frame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;

	Sprite** m_pSprites;
	Sprite* m_oldWiseSprite;
	Sprite* m_oldWiseTextbox1;
	Sprite* m_oldWiseTextbox2;
	Sprite* m_rail;
	Sprite* m_platform;
	ParallaxLayer* m_parallaxLayer;
	Node* m_moveNode;
	GameCamera* m_pCam;
	Sprite* m_pSawyer;
	Player* m_pPlayer;

	float m_timeElapsed;
	float m_timeToElapse;
	int m_page;
};

#endif // !_STORYSCENE_H_
