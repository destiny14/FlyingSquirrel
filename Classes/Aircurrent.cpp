#include "Aircurrent.h"
#include "MainLayer.h"
#include "PlayerCollider.h"
#include "Player.h"

Aircurrent::Aircurrent()
{

}

Aircurrent* Aircurrent::create(MainLayer* _layer, Point _dir, Size _size)
{
	Aircurrent* ret = new Aircurrent();

	if (ret && ret->init())
	{
		ret->autorelease();
		ret->addComponent(Collider::create(_size.width, _size.height));
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
	Node::update(_dt);

	Player* player = m_pLayer->getPlayer();
	Collider* col = dynamic_cast<Collider*>(this->getComponent("collider"));
	PlayerCollider* pCol = player->getPlayerColliderComponent();

	if ((pCol->getLeftCollider().intersectsRect(col->getCollisionRectangle()) || pCol->getRightCollider().intersectsRect(col->getCollisionRectangle())) && !player->getGrounded())
	{
		Point add = m_dir * _dt;
		player->addVelocity(add.x, add.y);
	}
}