#ifndef __PLAYERCOLLIDER_H__
#define __PLAYERCOLLIDER_H__

#include "cocos2d.h"

USING_NS_CC;

class PlayerCollider : public Component
{
public:
	static PlayerCollider* create(float w, float h);

	PlayerCollider();
	PlayerCollider(float x, float y);
	virtual ~PlayerCollider();

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);
	
	Rect getLeftCollider();
	Rect getRightCollider();
	Rect getBottomCollider();

	void setLeftCollider(float width, float height);
	void setRightCollider(float width, float height);
	void setBottomCollider(float width, float height);

private:
	Rect m_leftCollider;
	Rect m_rightCollider;
	Rect m_bottomCollider;
};

#endif // !__PLAYERCOLLIDER_H__
