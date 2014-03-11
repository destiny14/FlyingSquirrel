#include "cocos2d.h"
#include "Shooter.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Collider.h"
#include "Bullet.h"
#include <list>
#include <iterator>

USING_NS_CC;
using namespace std;

Shooter* Shooter::create(PhysicsEngine* _pEn, char* filename, MainLayer* parent)
{
	Shooter* shooter = new Shooter(_pEn);
	Texture* tex = Texture::create(filename);

	if (tex)
	{
		shooter->setTexture(tex);
		shooter->setParent(parent);

		shooter->init();

		return shooter;
	}
	else
	{
		return nullptr;
	}
}

Shooter::Shooter(PhysicsEngine* _pEn) : Moveable(_pEn) {}
Shooter::~Shooter() {}

bool Shooter::init()
{
	return true;
}

void Shooter::update(float dt)
{
	Moveable::update(dt);

	if (!this->nuts.empty())
	{
		for (Bullet* n : this->nuts)
		{
			n->update(dt);
		}
	}
	if (!this->nutsToDelete.empty())
	{
		bool deleteItr = false;
		for (list<Bullet*>::iterator itr = nuts.begin(); itr != nuts.end();)
		{
			for (list<Bullet*>::iterator itr2 = nutsToDelete.begin(); itr2 != nutsToDelete.end();)
			{
				if (*itr == *itr2)
				{
					itr = nuts.erase(itr);
					itr2 = nutsToDelete.erase(itr2);
					deleteItr = true;
				}
				else
				{
					++itr2;
				}
			}
			if (deleteItr)
			{
				deleteItr = false;
			}
			else
			{
				++itr;
			}
		}
	}
}
void Shooter::deleteBullet(Bullet* bullet)
{
	nutsToDelete.push_back(bullet);
}