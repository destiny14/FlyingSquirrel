#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include "LevelLayer.h"

using namespace std;
USING_NS_CC;

class Level
{
public:
	Level();
	~Level();

	list<layer> GetLayers();



	bool AddGroundBox();
private:
	LevelLayer[] m_layers;
};

#endif