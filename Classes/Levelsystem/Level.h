#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Level
{
public:
	static Level* createFromFile(const char* filename);

	Level();
	~Level();
private:
	void dump_to_stdout(const char* pFilename);
};

#endif