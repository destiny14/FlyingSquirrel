#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "cocos2d.h"

USING_NS_CC;

class Texture
{
public:
	Texture(char*, Rect);
	~Texture();

	void setSprite(Sprite* sprite);
	Sprite* getSprite();

	Rect getBoundingBox();
private:
	Sprite* m_sprite;
};

#endif // !__TEXTURE_H__
