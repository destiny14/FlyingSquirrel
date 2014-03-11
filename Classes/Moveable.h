#ifndef __MOVEABLE_H__
#define __MOVEABLE_H__

#include "cocos2d.h"
#include "Ground.h"
#include <list>

USING_NS_CC;

class MainLayer;

class Moveable : public Ground
{
public:

	Moveable(PhysicsEngine* _pEn);
	~Moveable();

	// bestimmt, ob das Objekt von Gravitation beeinflusst wird
	void setAffectedByGravity(bool affectedByGravity) { m_affectedByGravity = affectedByGravity; }
	bool getAffectedByGrafity() { return m_affectedByGravity; }

	// bestimmt, ob sich das Objekt auf dem Boden befindet
	bool isGrounded() { return m_grounded; }

	void setParentLayer(MainLayer* parent) { m_parent = parent; }
	MainLayer* getParentLayer() { return m_parent; }

	virtual void update(float dt) override;
	virtual Collider* getCollider() override { return collider; }
	virtual bool onCollision(PhysicsObject* _other, int myColliderTag) override;

	void setSize(float _w, float _h);
	void setSizeToTexture();
private:
	bool m_affectedByGravity;
	bool m_grounded;
	float m_gravity;
	MainLayer* m_parent;
	CompoundCollider* collider;
	AABBCollider* up;
	AABBCollider* bot;
	AABBCollider* left;
	AABBCollider* right;
};

#endif // !__MOVEABLE_H__
