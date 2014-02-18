#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "..\Components\Collider.h"
#include "Layers\MainLayer.h"

class Bullet : Moveable
{
public:
	static Bullet* create(char* filename, MainLayer* parent, Point* position);

	Bullet();
	~Bullet();

	virtual bool init();
	virtual void update(float dt);

protected:

private:
	void setCollider();
	void destroy();
};

#endif // !__BULLET_H__