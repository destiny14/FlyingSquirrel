#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "cocos2d.h"
#include "Logfile.h"

#define g_pLogfile CLogfile::Get ()

USING_NS_CC;

class Texture
{
public:
	Texture(char*, float, float);
	~Texture();

	void setSprite(Sprite* sprite);
	Sprite* getSprite();

	Rect getBoundingBox();
private:
	Sprite* m_sprite;
};

#endif // !__TEXTURE_H__
