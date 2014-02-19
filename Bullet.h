#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "..\Components\Collider.h"
#include "Layers\MainLayer.h"

enum Bullettype
{
	Nut = 0,
	Fireball = 1,
	Shockwave = 2
};

class Bullet : Moveable
{
public:
	Bullet* createNut(MainLayer* parent, Point* position, Point* direction, float force);

	Bullet();
	~Bullet();

	virtual bool init();
	virtual void update(float dt);

protected:

private:
	void setCollider();
	void destroy();

	Bullettype m_bullettype;
	Point* m_pDirection;
	float m_force;
};

#endif // !__BULLET_H__