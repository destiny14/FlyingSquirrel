#ifndef __PHYSICSOBJECT_H__
#define __PHYSICSOBJECT_H__

#include "cocos2d.h"
#include "Collider.h"

#define MAX_INTERPOLATIONCHECKS 10
#define MAX_MOVEINTERVALL 0.3f

USING_NS_CC;

class PhysicsEngine;

class PhysicsObject : public Node
{
public:
	PhysicsObject(PhysicsEngine* _engine);
	virtual Collider* getCollider() = 0;
	virtual void update(float _dt) override;
	//Gibt zurueck, ob die Collision bei Bewegung ignoriert werden sollte, d.h. nicht blockt
	virtual bool onCollision(PhysicsObject* _other, int myColliderTag);
	virtual int getTag() = 0;
protected:
	Point velocity = Point::ZERO;
private:
	PhysicsEngine* m_pEngine = nullptr;
};

#endif