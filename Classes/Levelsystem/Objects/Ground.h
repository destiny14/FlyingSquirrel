#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Texture.h"

USING_NS_CC;

class Ground : public Node
{
public:
	static Ground* create(char* filename);

	Ground();
	~Ground();

	void setCollisionRectangle();
	void setCollisionRectangle(float width, float height);
	Rect getCollisionRectangle();

	// use setPosition(float, float) instead, it's faster
	void setPosition(const Point& pos);
	void setPosition(float x, float y);

	Sprite* getSprite();

	void setTexture(Texture* texture);
	Texture* getTexture();


private:
	Texture* m_texture;
	Rect m_collisionRectangle;
};

#endif // !__GROUND_H__
