#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define PTM_RATIO 32.0f

#include "GLES-Render.h"
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();

	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void tick(float dt);

	virtual void draw();
	
	// a selector callback
    void menuCloseCallback(Object* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	GLESDebugDraw* m_debugDraw;
	b2World* m_world;
	b2Body* m_box;
};

#endif // __HELLOWORLD_SCENE_H__
