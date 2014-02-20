#include "GameCamera.h"

GameCamera::GameCamera(Node* _follower)
{
	m_pFollow = _follower;
	m_pFollowed = nullptr;
	m_bounds = Rect::ZERO;
	m_rot = 0.0f;
	m_lsd = false;
}

GameCamera::~GameCamera()
{

}

void GameCamera::setBoundingRect(Rect _bounds)
{
	m_bounds = _bounds;

	if (Rect::ZERO.equals(m_bounds)) return;

	Size winSize = Director::getInstance()->getWinSize();
	Point _fullScreenSize = Point(winSize.width, winSize.height);

	float _leftBoundary = -((m_bounds.origin.x + m_bounds.size.width) - _fullScreenSize.x);
	float _rightBoundary = -m_bounds.origin.x;
	float _topBoundary = -m_bounds.origin.y;
	float _bottomBoundary = -((m_bounds.origin.y + m_bounds.size.height) - _fullScreenSize.y);

	if (_rightBoundary < _leftBoundary)
	{
		// screen width is larger than world's boundary width
		//set both in the middle of the world
		_rightBoundary = _leftBoundary = (_leftBoundary + _rightBoundary) / 2;
	}
	if (_topBoundary < _bottomBoundary)
	{
		// screen width is larger than world's boundary width
		//set both in the middle of the world
		_topBoundary = _bottomBoundary = (_topBoundary + _bottomBoundary) / 2;
	}

	m_camBounds = Rect(_leftBoundary, _bottomBoundary, _rightBoundary - _leftBoundary, _topBoundary - _bottomBoundary);
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
	updateLSD(_dt);
	if (m_pFollow == nullptr || m_pFollowed == nullptr) return;

	Point target = clamp(m_bounds, m_pFollowed->getPosition());
	m_pFollowed->setPosition(target);

	Size size = EGLView::getInstance()->getVisibleSize() * 0.5f;
	Point tmp = target;
	tmp.x *= -1.0f;
	tmp.y *= -1.0f;
	tmp += Point(size.width, size.height);
	tmp = m_pFollow->getPosition().lerp(tmp, 0.6f);
	tmp = clamp(m_camBounds, tmp);
	m_pFollow->setPosition(tmp);
}

void GameCamera::updateLSD(float dt)
{
	if (m_lsd)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(45.0f * dt, 0.0f, 0.0f, 1.0f);
		m_rot += 45.0f * dt;
		kmGLTranslatef(-400.0f, -300.0f, 0.0f);
	}
	else if (m_rot != 0.0f)
	{
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLTranslatef(400.0f, 300.0f, 0.0f);
		kmGLRotatef(-m_rot, 0.0f, 0.0f, 1.0f);
		m_rot = 0.0f;
		kmGLTranslatef(-400.0f, -300.0f, 0.0f);
	}
}

Point GameCamera::clamp(Rect _b, Point _p)
{
	if (Rect::ZERO.equals(_b)) return _p;

	return Point(
		clampf(_p.x, _b.getMinX(), _b.getMaxX()),
		clampf(_p.y, _b.getMinY(), _b.getMaxY())
		);
}