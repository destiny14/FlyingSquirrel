#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "Ground.h"

class Player;
class MainLayer;

class Collectible : public Ground
{
public:
	Collectible(MainLayer* parent);
	bool init() override;

	virtual bool onCollision(PhysicsObject* _other, int myColliderTag) override;
	virtual int getTag() override { return TAG_COLLECTIBLE; }
protected:
	void deleteCollectible();
	virtual void initCollectible() = 0;
	virtual void onCollidedWithPlayer(Player* _player) = 0;
private:
	MainLayer* m_pLayer;
	void collisionCheck();
};

#endif