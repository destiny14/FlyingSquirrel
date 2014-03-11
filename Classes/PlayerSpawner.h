#ifndef __PLAYERSPAWNER_H__
#define __PLAYERSPAWNER_H__

#include "cocos2d.h"

USING_NS_CC;

class PlayerSpawner
{
public:
	PlayerSpawner(Point position);
	~PlayerSpawner();

	Point getSpawnPosition();
	void setSpawnPosition(Point spawn);
	void setSpawnPosition(float x, float y);
private:
	Point m_spawnPosition;
};

#endif // !__PLAYERSPAWNER_H__
