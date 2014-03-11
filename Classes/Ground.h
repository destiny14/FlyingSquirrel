#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Physic.h"
#include "Texture.h"

USING_NS_CC;

class Ground : public PhysicsObject
{
public:
	static Ground* create(PhysicsEngine* _pEn, char* filename);

	Ground(PhysicsEngine* _pEn);
	~Ground();

	Sprite* getSprite();
	void setTexture(Texture* texture);
	Texture* getTexture();

	virtual void update(float _dt) override { PhysicsObject::update(_dt); if(m_texture->getPosition() != getPosition()) m_texture->setPosition(getPosition()); }
	virtual Collider* getCollider() override { return m_pCol; }
	virtual int getTag() override { return TAG_GROUND; }
private:
	Texture* m_texture;
	AABBCollider* m_pCol;
};

#endif // !__GROUND_H__
