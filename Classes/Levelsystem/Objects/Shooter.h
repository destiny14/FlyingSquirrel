#ifndef __SHOOTER_H__
#define __SHOOTER_H__

#include "cocos2d.h"
#include "Bullet.h"
#include <list>

class Shooter : public Moveable
{
public:

	static Shooter* Shooter::create();

	Shooter();
	~Shooter();

	virtual bool init();
	virtual void update();

	void deleteBullet();
	list<Bullet*>* nuts;

protected:

private:

};

#endif // !__SHOOTER_H__