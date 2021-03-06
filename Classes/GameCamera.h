#ifndef __GAMECAMERA_H__
#define __GAMECAMERA_H__

#include "cocos2d.h"

USING_NS_CC;

class GameCamera
{
public:
	GameCamera(Node* _follower);
	~GameCamera();

	void setBoundingRect(Rect _bounds);
	void setFollowTarget(Node* _followed);
	void setFollower(Node* _follower);
	void update(float _dt);
	void toggleLSD() { m_lsd = !m_lsd; }
private:
	Node* m_pFollow;
	Node* m_pFollowed;
	Rect m_bounds;
	Rect m_camBounds;
	float m_rot;
	bool m_lsd;

	void updateLSD(float dt);
	Point clamp(Rect _b, Point _p);
};

#endif