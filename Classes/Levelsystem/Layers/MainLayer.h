#ifndef __MAINLAYER_H__
#define __MAINLAYER_H__

#include "cocos2d.h"
#include "LevelLayer.h"
#include "..\InputManager.h"
//#include "../../InputManager.h"

class Player;
class GameCamera;
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
	GameCamera* m_pCam;
	InputManager* m_pInput;
	Player* m_pPlayer;
	list<Ground*>* m_physicObjects;
};

#endif // !__MAINLAYER_H__
