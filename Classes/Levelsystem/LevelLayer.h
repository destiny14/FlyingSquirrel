#ifndef __LEVELLAYER_H__
#define __LEVELLAYER_H__

#include "cocos2d.h"
#include "..\Objects\Texture.h"
#include "..\Objects\Ground.h"
#include <list>

using namespace std;

class LevelLayer : public cocos2d::Layer
{
public:
	LevelLayer();
	~LevelLayer();

	void setTextures(list<Texture*>* textures);
	list<Texture*>* getTextures();

	void setName(char* name);
	char* getName();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();
private:
	list<Texture*>* m_textures;
	char* m_name;
};

#endif // !__LEVELLAYER_H__
