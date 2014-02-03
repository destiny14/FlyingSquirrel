#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "LevelLayer.h"

class Player : public Moveable
{
public:
	static Player* create(char* filename, LevelLayer* parent);

	Player();
	~Player();

	virtual void update(float dt);

	// setCollider()
	//
	// setzt die Kollider entsprechend der gesetzten Texur
	void setCollider();

	void updateCollider();

	Rect getLeftCollider();
	Rect getRightCollider();
	Rect getBottomCollider();

	void setLeftCollider(float width, float height);
	void setRightCollider(float width, float height);
	void setBottomCollider(float width, float height);

private:
	void CheckForCollisions();
	Rect m_leftCollider;
	Rect m_rightCollider;
	Rect m_bottomCollider;
};

#endif // !__PLAYER_H__
