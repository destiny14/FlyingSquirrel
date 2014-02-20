#ifndef __MAINLAYER_H__
#define __MAINLAYER_H__

#include "cocos2d.h"
#include "LevelLayer.h"
#include "..\InputManager.h"
#include "Objects\PlayerSpawner.h"
//#include "../../InputManager.h"


class Player;
class GameCamera;
class InputManager;
class InputAction;
class MouseInputAction;

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

	PlayerSpawner* getPlayerSpawner();
	void setPlayerSpawner(PlayerSpawner* ps);
private:
	PlayerSpawner* m_playerSpawner;
	GameCamera* m_pCam;
	InputManager* m_pInput;
	InputAction* m_pLSD;
	Player* m_pPlayer;
	list<Ground*>* m_physicObjects;
	MouseInputAction* _test;
};

#endif // !__MAINLAYER_H__
