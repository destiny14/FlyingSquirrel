#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "Texture.h"

USING_NS_CC;

class Ground
{
public:
	Ground(Texture* texture);
	~Ground();

	void setTexture(Texture* texture);
	Texture* getTexture();


private:
	Texture* m_texture;
};

#endif // !__GROUND_H__
