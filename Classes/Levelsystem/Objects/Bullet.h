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

class Bullet : public Moveable
{
public:
	static Bullet* createNut(Moveable* shooter, MainLayer* parent, Point position, float direction, float force);

	Bullet();
	~Bullet();

	virtual bool init(Moveable* shooter, float direction, float force);
	virtual void update(float dt);

protected:

private:
	void setCollider();
	void destroy();
	void CheckForCollisions();

	Moveable* m_shooter;
	Bullettype m_bullettype;
	float m_direction;
	float m_force;
};

#endif // !__BULLET_H__