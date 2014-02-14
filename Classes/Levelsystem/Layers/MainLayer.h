#ifndef __MAINLAYER_H__
#define __MAINLAYER_H__

#include "cocos2d.h"
#include "LevelLayer.h"

class MainLayer : public LevelLayer
{
public:
	MainLayer();
	~MainLayer();

	static MainLayer* create();

	virtual bool init();

	virtual void update(float dt);

	virtual void draw();

	void setPhysicsObjects(list<Ground*>* physicObjects);

	list<Ground*>* getPhysicsObjects();
private:

	list<Ground*>* m_physicObjects;
};

#endif // !__MAINLAYER_H__
