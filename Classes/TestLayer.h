#ifndef __TESTLAYER_H__
#define	__TESTLAYER_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class TestLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(TestLayer);
};

#endif // !__TESTLAYER_H__
