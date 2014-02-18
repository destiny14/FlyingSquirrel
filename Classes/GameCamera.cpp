#include "GameCamera.h"

GameCamera::GameCamera(Node* _follower)
{
	m_pFollow = _follower;
	m_pFollowed = nullptr;
	m_bounds = Rect::ZERO;
}

GameCamera::~GameCamera()
{

}

void GameCamera::setBoundingRect(Rect _bounds)
{
	m_bounds = _bounds;
}

void GameCamera::setFollowTarget(Node* _followed)
{
	m_pFollowed = _followed;
}

void GameCamera::setFollower(Node* _follower)
{
	m_pFollow = _follower;
}

void GameCamera::update(float _dt)
{
	if (m_pFollow == nullptr || m_pFollowed == nullptr) return;

	Point tmp = m_pFollowed->getPosition();
	tmp.x *= -1.0f;
	tmp.y *= -1.0f;
	Size size = EGLView::getInstance()->getFrameSize() * 0.5f;
	tmp += Point(size.width, size.height);

	tmp = m_pFollow->getPosition().lerp(tmp, 0.6f);

	if (!m_bounds.equals(Rect::ZERO))
	{
		m_pFollow->setPosition(Point(
			clampf(tmp.x, m_bounds.getMinX(), m_bounds.getMaxX()),
			clampf(tmp.y, m_bounds.getMinY(), m_bounds.getMaxY()))
			);
	}
	else
	{
		m_pFollow->setPosition(tmp);
	}
}