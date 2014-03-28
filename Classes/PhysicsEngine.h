#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__

#include "Collider.h"
#include "PhysicsObject.h"
#include <list>

class PhysicsEngine
{
public:
	bool checkForBlockingCollision(PhysicsObject* _obj);
	void addPhysicsObject(PhysicsObject* _obj);
	void removePhysicsObject(PhysicsObject* _obj);

	void draw();
private:
	std::list<PhysicsObject*> m_list;
	std::list<PhysicsObject*> m_objectsToRemove;
	bool isCollision(Collider* _c1, Collider* _c2);
	bool isCollision(AABBCollider* _c1, Collider* _c2);
	bool isCollision(CompoundCollider* _c1, Collider* _c2);
	bool isCollision(AABBCollider* _c1, AABBCollider* _c2);
	bool isCollision(CompoundCollider* _c1, AABBCollider* _c2);
	bool isCollision(AABBCollider* _c1, CompoundCollider* _c2);
	bool isCollision(CompoundCollider* _c1, CompoundCollider* _c2);
};

#endif