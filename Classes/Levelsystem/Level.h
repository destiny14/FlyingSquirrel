#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include <list>

using namespace std;
USING_NS_CC;

class Level
{
public:
	Level();
	~Level();

	bool AddGroundBox();
private:
	list<GroundBox> m_groundBoxes;
};

#endif