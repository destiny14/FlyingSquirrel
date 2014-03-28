#include "Aircurrent.h"
#include "MainLayer.h"

Aircurrent::Aircurrent(PhysicsEngine* _pEn) : PhysicsObject(_pEn)
{

}

Aircurrent* Aircurrent::create(PhysicsEngine* _pEn, MainLayer* _layer, Point _dir, Size _size)
{
	Aircurrent* ret = new Aircurrent(_pEn);

	if (ret && ret->init())
	{
		ret->autorelease();
		ret->m_pCol->setBoundingRect(Rect(0.0f, 0.0f,_size.width, _size.height));
		ret->m_dir = _dir;
		ret->m_pLayer = _layer;
		ret->setTag(TAG_AIR);
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

void Aircurrent::update(float _dt)
{
	velocity = Point::ZERO;
	PhysicsObject::update(_dt);
	m_dt = _dt;
}

bool Aircurrent::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (_other->getTag() != TAG_PLAYER) return false;

	Point add = m_dir * m_dt;
	_other->velocity += add;

	return false;
}