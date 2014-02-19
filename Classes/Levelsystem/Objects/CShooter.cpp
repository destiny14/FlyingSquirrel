#include "cocos2d.h"
#include "Shooter.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "..\Components\Collider.h"
#include "Bullet.h"
#include <list>

USING_NS_CC;
using namespace std;

Shooter* Shooter::create()
{
	Shooter* shooter = new Shooter();
	return shooter;
}

Shooter::Shooter() {}
Shooter::~Shooter() {}

bool Shooter::init()
{
	return true;
}

void Shooter::update()
{

}

void Shooter::deleteBullet()
{

}