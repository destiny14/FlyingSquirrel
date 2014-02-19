#include "cocos2d.h"
#include "Shooter.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "..\Components\Collider.h"
#include "Bullet.h"
#include <list>

USING_NS_CC;
using namespace std;

Shooter* Shooter::create(char* filename, MainLayer* parent)
{
	Shooter* shooter = new Shooter();
	Texture* tex = Texture::create(filename);

	if (tex)
	{
		shooter->setTexture(tex);
		shooter->setCollider();
		shooter->setParent(parent);
		shooter->setGround(false);

		shooter->init();

		return shooter;
	}
	else
	{
		return nullptr;
	}
}

Shooter::Shooter() { nuts = nullptr; }
Shooter::~Shooter() {}

bool Shooter::init()
{
	return true;
}

void Shooter::update(float dt, bool overwriteCollisionCheck)
{
	if (nuts == nullptr)
		nuts = new list<Bullet*>();
	Moveable::update(dt, overwriteCollisionCheck);

	if (!this->nuts->empty())
	{
		for (Bullet* n : *this->nuts)
		{
			n->update(dt);
		}
	}
}

void Shooter::deleteBullet()
{

}