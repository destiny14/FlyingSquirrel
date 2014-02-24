#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "Collider.h"
#include "MainLayer.h"
#include "Shooter.h"
#include "Snail.h"
#include "SlimeHeap.h"
#include "Mantis.h"

enum Bullettype
{
	Nut = 0,
	Fireball = 1,
	Shockwave = 2
};

class Bullet : public Moveable
{
public:
	static Bullet* createNut(Shooter* shooter, MainLayer* parent, Point position, float direction, float force);

	Bullet();
	~Bullet();

	virtual bool init(Shooter* shooter, float direction, float force);
	virtual void update(float dt);

protected:

private:
	void setCollider();
	void destroy();
	void CheckForCollisions();

	Shooter* m_shooter;
	Bullettype m_bullettype;
	float m_direction;
	float m_force;

	Mantis* m_pMantis = nullptr;
	Snail* m_pSnail = nullptr;
	SlimeHeap* m_pSlimeHeap = nullptr;
};

#endif // !__BULLET_H__