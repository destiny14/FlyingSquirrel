#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "..\Components\Collider.h"
#include "Texture.h"

USING_NS_CC;

class Ground : public Node
{
public:
	static Ground* create(char* filename);

	Ground();
	~Ground();

	void setCollider();
	void setCollider(float width, float height);
	Collider* getColliderComponent();

	// use setPosition(float, float) instead, it's faster
	void setPosition(const Point& pos) override;
	void setPosition(float x, float y) override;

	Sprite* getSprite();

	void setTexture(Texture* texture);
	Texture* getTexture();

	void setGround(bool);
	bool getGround();

	void setWall(bool _w) { m_isWall = _w; }
	bool getWall() { return m_isWall; }
private:
	Texture* m_texture;
	Rect m_collisionRectangle;
	bool m_isGround;
	bool m_isWall;
};

#endif // !__GROUND_H__
