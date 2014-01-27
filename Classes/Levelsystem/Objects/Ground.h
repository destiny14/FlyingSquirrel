#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Texture.h"

USING_NS_CC;

class Ground
{
public:
	Ground(Texture* texture, Rect location, const b2Vec2* vertices, int vertexCount);
	~Ground();

	void init(b2World* world);

	void draw();

	void setTexture(Texture* texture);
	Texture* getTexture();

	void setSprite(Sprite* sprite);
	Sprite* getSprite();

private:
	Texture* m_texture;
	Sprite* m_sprite;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
};

#endif // !__GROUND_H__
