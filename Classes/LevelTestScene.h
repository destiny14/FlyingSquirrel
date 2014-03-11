#ifndef __LEVELTESTSCENE_H__
#define __LEVELTESTSCENE_H__

#include "cocos2d.h"
#include "MainLayer.h"
#include "Level.h"

class LevelTestScene : public cocos2d::Layer
{
public:
	LevelTestScene();
	~LevelTestScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	virtual void draw();

	CREATE_FUNC(LevelTestScene);
};

#endif // !__LEVELTESTSCENE_H__