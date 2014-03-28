#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "cocos2d.h"
#include <list>

enum ColliderType
{
	AABB,
	COMPOUND,
	CIRCLE
};

class PhysicsObject;

class Collider {
public:
	virtual void update() = 0;
	virtual ColliderType getColliderType() = 0;
	virtual void setPhysicsObject(PhysicsObject* _obj) { m_obj = _obj; }
	PhysicsObject* getPhysicsObject() { return m_obj; }
	void setTag(int _tag) { m_tag = _tag; }
	int getTag() { return m_tag; }

	virtual void debugDraw() = 0;
private:
	int m_tag = -1;
	PhysicsObject* m_obj = nullptr;
};

class CompoundCollider : public Collider
{
public:
	virtual void update() override;
	virtual ColliderType getColliderType() override { return ColliderType::COMPOUND; }
	virtual void setPhysicsObject(PhysicsObject* _obj) override;
	void addCollider(Collider* _col);
	void remCollider(Collider* _col);
	std::list<Collider*>* getColliders();

	virtual void debugDraw() override;
private:
	std::list<Collider*> m_list;
};

class AABBCollider : public Collider
{
public:
	virtual void update() override;
	virtual ColliderType getColliderType() override { return ColliderType::AABB; }
	void setBoundingRect(cocos2d::Rect _bounds) { m_bounds = _bounds; }
	cocos2d::Rect getBoundingRect() { return m_bounds; }

	virtual void debugDraw() override;
private:
	cocos2d::Rect m_bounds;
};
#endif