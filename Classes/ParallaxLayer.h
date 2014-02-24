#ifndef __PARALLAXLAYER_H__
#define __PARALLAXLAYER_H__
#include "LevelLayer.h"

class ParallaxLayer : public LevelLayer {
public:
	static ParallaxLayer* create();
	
	ParallaxLayer();
	virtual ~ParallaxLayer();
	void addParallaxElement(Sprite* _tex, Point &_pos, Point &_parallaxRatio, int _order);
protected:
	void initParallax();
	void cleanParallax();

private:
	ParallaxNode* m_pNode;
};

#endif