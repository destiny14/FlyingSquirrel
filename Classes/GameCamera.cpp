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

	Point target = clamp(m_bounds, m_pFollowed->getPosition());
	m_pFollowed->setPosition(target);

	Size size = EGLView::getInstance()->getVisibleSize() * 0.5f;

	Point tmp = target;
	tmp.x *= -1.0f;
	tmp.y *= -1.0f;
	tmp += Point(size.width, size.height);
	tmp = m_pFollow->getPosition().lerp(tmp, 0.6f);
	tmp = clamp(m_bounds, tmp);
	m_pFollow->setPosition(tmp);
}

Point GameCamera::clamp(Rect _b, Point _p)
{
	if (Rect::ZERO.equals(_b)) return _p;

	return Point(
		clampf(_p.x, _b.getMinX(), _b.getMaxX()),
		clampf(_p.y, _b.getMinY(), _b.getMaxY())
		);
}