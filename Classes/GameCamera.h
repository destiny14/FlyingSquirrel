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
private:
	Node* m_pFollow;
	Node* m_pFollowed;
	Rect m_bounds;
};

#endif