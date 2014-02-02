#ifndef __LEVELLAYER_H__
#define __LEVELLAYER_H__

#include "cocos2d.h"
#include "Texture.h"
#include "Ground.h"
#include <list>

using namespace std;

class LevelLayer : public cocos2d::Layer
{
public:
	LevelLayer();
	~LevelLayer();

	void setTextures(list<Texture*> textures);
	list<Texture*> getTextures();

	void setPhysicsObjects(list<Ground*> physicObjects);

	list<Ground*> getPhysicsObjects();

	void setName(char* name);
	char* getName();
private:
	list<Texture*> m_textures;
	list<Ground*> m_physicObjects;
	char* m_name;
};

#endif // !__LEVELLAYER_H__
