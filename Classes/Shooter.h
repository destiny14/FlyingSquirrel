#ifndef __SHOOTER_H__
#define __SHOOTER_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "PlayerCollider.h"
#include "MainLayer.h"
#include <list>

class Bullet;

class Shooter : public Moveable
{
public:

	static Shooter* Shooter::create(char* filename, MainLayer* parent);

	Shooter();
	~Shooter();

	virtual bool init();
	virtual void update(float dt, bool overwriteCollisionCheck = false);

	void deleteBullet(Bullet* bullet);
	void killBullet(Bullet* bullet);
	list<Bullet*> nuts;

protected:

private:
	list<Bullet*> nutsToDelete;

};

#endif // !__SHOOTER_H__