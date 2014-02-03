#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "cocos2d.h"

USING_NS_CC;


class Collider : public Component
{
public:
	Collider();
	Collider(float x, float y);
	virtual ~Collider();

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float dt);
	virtual bool serialize(void* r);

	void setCollisionRectangle(Rect collisionRectangle);
	Rect getCollisionRectangle();

	static Collider* create(float w, float h);
private:
	Rect m_collisionRectangle;
};

#endif // !__COLLIDER_H__
