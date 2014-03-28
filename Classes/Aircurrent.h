#ifndef __AIRCURRENT_H__
#define __AIRCURRENT_H__

#define TAG_AIR 12365798

#include "Physic.h"

class MainLayer;

class Aircurrent : public PhysicsObject
{
public:
	static Aircurrent* create(PhysicsEngine* _pEn, MainLayer* _layer, Point _dir, Size _size);
	void update(float _dt) override;
	Point getDirection() { return m_dir; }
	Size getSize() { return m_pCol->getBoundingRect().size; }

	virtual bool onCollision(PhysicsObject* _other, int myColliderTag);
	virtual int getTag() override { return TAG_AIRCURRENT; }
	virtual Collider* getCollider() override { return m_pCol; }
private:
	Aircurrent(PhysicsEngine* _pEn);

	AABBCollider* m_pCol;
	MainLayer* m_pLayer;
	Point m_dir;
	float m_dt;
};

#endif