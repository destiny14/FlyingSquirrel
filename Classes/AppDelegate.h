#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#define RES_VERSION "1.1"

#include "cocos2d.h"
#include "Box2D\Box2D.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

	/**
	@brief Sets the desired FPS, if the parameter is <= 0, the setting will not be changed, only actualised
	*/
	void setDesiredFPS(int);

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

private:
	b2World* m_world;
	int m_desiredFPS;
};

#endif // _APP_DELEGATE_H_

