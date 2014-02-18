#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Ground.h"
#include "Texture.h"
#include "Moveable.h"
#include <queue>
#include "cocos2d.h"
#include "Levelsystem\LevelLayer.h"
#include "Levelsystem\Objects\Player.h"
#include "Levelsystem\Layers\MainLayer.h"
#include "GameCamera.h"

class HelloWorld : public MainLayer
{
public:
	HelloWorld();

	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	virtual void update(float dt);

	virtual void draw();
	
	// a selector callback
    void menuCloseCallback(Object* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	InputManager* m_pInput;
	InputAction* m_pLSD;
	Player* m_moveable;
	GameCamera* m_pCam;
	Ground* m_ground;
	bool m_lsd;
	float m_rot;
};

#endif // __HELLOWORLD_SCENE_H__
