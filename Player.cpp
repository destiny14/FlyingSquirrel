#include "cocos2d.h"
#include "Player.h"


CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}





void CPlayer::update(float dt)
{
	PlayerCollider::update(dt);

	if (m_pForward->isPressed && m_isGrounded)
	{
		getOwner()->setPositionX = getOwner()->getPositionX + 1.0f;
	}
	if (m_pBackward->isPressed && m_isGrounded)
	{
		getOwner()->setPositionX = getOwner()->getPositionX - 1.0f;
	}
	if (m_pJump->isPressed && m_isGrounded)
	{
		getOwner()->setPositionY = getOwner()->getPositionY + 6.0f;
		m_isGrounded = false;
	}
	if (m_pJump->isPressed && !m_isGrounded)
	{

	}

}
