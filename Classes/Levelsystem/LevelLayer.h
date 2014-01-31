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
	void SetTextures(list<Texture> textures)
	{
		m_textures = textures;
	}
	list<Texture> GetTextures()
	{
		return m_textures;
	}

	void SetPhysicsObjects(list<Ground*> physicObjects)
	{
		m_physicObjects = physicObjects;
	}

	list<Ground*> GetPhysicsObjects()
	{
		return m_physicObjects;
	}

	void SetName(char* name)
	{
		m_name = name;
	}
	char* GetName()
	{
		return m_name;
	}
private:
	list<Texture> m_textures;
	list<Ground*> m_physicObjects;
	char* m_name;
};

#endif // !__LEVELLAYER_H__
