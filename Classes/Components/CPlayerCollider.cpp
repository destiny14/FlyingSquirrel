#include "cocos2d.h"
#include "PlayerCollider.h"

PlayerCollider* PlayerCollider::create(float width, float height)
{
	PlayerCollider* col = new PlayerCollider(width, height);
	if (col)
	{
		col->setName("playerCollider");
		col->autorelease();
		return col;
	}
	CC_SAFE_DELETE(col);
	return nullptr;
}

PlayerCollider::PlayerCollider() {}

PlayerCollider::PlayerCollider(float width, float height) 
{
	m_leftCollider = Rect(0, 0, width * 0.5, height);
	m_rightCollider = Rect(0, 0, width * 0.5, height);
	m_bottomCollider = Rect(0, 0, width * 0.5, 3);
}

PlayerCollider::~PlayerCollider() {}

bool PlayerCollider::init()
{
	return true;
}

void PlayerCollider::onEnter()
{
	update(0.0f);
}

void PlayerCollider::onExit()
{

}

void PlayerCollider::update(float dt)
{
	Point p = getOwner()->getPosition();
	m_leftCollider.origin.x = p.x - m_leftCollider.size.width;
	m_leftCollider.origin.y = p.y - (0.5f * m_leftCollider.size.height);
	m_rightCollider.origin.x = p.x;
	m_rightCollider.origin.y = p.y - (0.5f * m_rightCollider.size.height);
	m_bottomCollider.origin.x = p.x - (0.5f * m_leftCollider.size.width);
	m_bottomCollider.origin.y = p.y - (0.5f * m_leftCollider.size.height) - 2;
}

Rect PlayerCollider::getLeftCollider() 
{
	return m_leftCollider;
}

Rect PlayerCollider::getRightCollider()
{
	return m_rightCollider;
}

Rect PlayerCollider::getBottomCollider()
{
	return m_bottomCollider;
}

void PlayerCollider::setLeftCollider(float width, float height)
{

}

void PlayerCollider::setRightCollider(float width, float height)
{

}

void PlayerCollider::setBottomCollider(float width, float height)
{

}