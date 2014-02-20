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

	virtual Player* getPlayer() { return m_pPlayer; }

	void setPhysicsObjects(list<Ground*>* physicObjects);

	void menuCloseCallback(Object* pSender);

	list<Ground*>* getPhysicsObjects();
protected:
	GameCamera* m_pCam;
	InputManager* m_pInput;
	InputAction* m_pLSD;
	Player* m_pPlayer;
	list<Ground*>* m_physicObjects;
	MouseInputAction* _test;
};

#endif // !__MAINLAYER_H__
