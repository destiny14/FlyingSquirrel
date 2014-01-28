#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Texture.h"

#define PTM_RATIO 32.0f

USING_NS_CC;

class Ground
{
public:
	Ground(Texture* texture);
	~Ground();

	void init(b2World* world);

	void setTexture(Texture* texture);
	Texture* getTexture();


private:
	Texture* m_texture;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_polyShape;
	b2FixtureDef m_fixtureDef;
};

#endif // !__GROUND_H__
