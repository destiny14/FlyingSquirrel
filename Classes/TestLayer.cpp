#include "TestLayer.h"
#include "cocos2d.h"

USING_NS_CC;

bool TestLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	

	auto lblText = "DOUBLE LAY0R!";
	auto label = LabelTTF::create(lblText, "Arial", 24);
	label->setPosition(Point(origin.x + 200, origin.y + 200));
	this->addChild(label, 1);
}