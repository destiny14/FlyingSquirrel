#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "cocos2d.h"
#include "Logfile.h"

#define g_pLogfile CLogfile::Get ()

USING_NS_CC;

class Texture : public Node
{
public:
	static Texture* create(char* filename);

	Texture();
	~Texture();

	// use setPosition(float, float) instead, it's faster
	void setPosition(const Point& pos);

	void setPosition(float x, float y);

	bool setSprite(Sprite* sprite);
	Sprite* getSprite();
private:
	Sprite* m_sprite;

};

#endif // !__TEXTURE_H__
