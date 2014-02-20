#include "cocos2d.h"
#include "Shooter.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "..\Components\Collider.h"
#include "Bullet.h"
#include <list>
#include <iterator>

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

Shooter::Shooter() {}
Shooter::~Shooter() {}

bool Shooter::init()
{
	return true;
}

void Shooter::update(float dt, bool overwriteCollisionCheck)
{
	Moveable::update(dt, overwriteCollisionCheck);

	if (!this->nuts.empty())
	{
		for (Bullet* n : this->nuts)
		{
			n->update(dt);
		}
	}
	if (!this->nutsToDelete.empty())
	{
		for (list<Bullet*>::iterator itr = nuts.begin(); itr != nuts.end(); ++itr)
		{
			for (list<Bullet*>::iterator itr2 = nutsToDelete.begin(); itr2 != nutsToDelete.end(); ++itr2)
			{
				if (itr == itr2)
				{
					nuts.remove(*itr);
					nutsToDelete.remove(*itr2);
				}
			}
		}
	}
}

void Shooter::deleteBullet(Bullet* bullet)
{
	nutsToDelete.push_back(bullet);
}