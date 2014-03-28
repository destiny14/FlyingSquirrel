#ifndef __PHYSICSOBJECT_H__
#define __PHYSICSOBJECT_H__

#include "cocos2d.h"
#include "Collider.h"

#define MAX_INTERPOLATIONCHECKS 50.0f
#define MAX_MOVEINTERVALL 0.15f

#define TAG_GROUND 0x000
#define TAG_PLAYER 0x001
#define TAG_COLLECTIBLE 0x002
#define TAG_AIRCURRENT 0x003
#define TAG_BULLET 0x004

USING_NS_CC;

class PhysicsEngine;

class PhysicsObject : public Node
{
public:
	PhysicsObject(PhysicsEngine* _engine);
	virtual Collider* getCollider() = 0;
	virtual void update(float _dt) override;
	//Gibt zurueck, ob die Collision bei Bewegung ignoriert werden sollte, d.h. nicht blockt
	virtual bool onCollision(PhysicsObject* _other, int myColliderTag) { return false; }
	virtual void onCollisionExit(PhysicsObject* _other, int myColliderTag) {}
	
	virtual int getTag() = 0;

	virtual void removeFromParentAndCleanup(bool _b) override;

	PhysicsEngine* getPhysicsEngine() { return m_pEngine; }

	Size size = Size(0.0f, 0.0f);
	Point velocity = Point::ZERO;

	bool isFlaggedForDeletion() { return flaggedForDeletion; }
	void flagForDeletion() { flaggedForDeletion = true; }
private:
	PhysicsEngine* m_pEngine = nullptr;
	bool flaggedForDeletion = false;
};

#endif