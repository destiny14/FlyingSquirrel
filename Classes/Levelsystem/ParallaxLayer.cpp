#include "ParallaxLayer.h"

ParallaxLayer* ParallaxLayer::create()
{
	ParallaxLayer* layer = new ParallaxLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

ParallaxLayer::ParallaxLayer()
{
	m_pNode = nullptr;
}

ParallaxLayer::~ParallaxLayer()
{
	cleanParallax();
}

void ParallaxLayer::initParallax()
{
	if (m_pNode != nullptr) cleanParallax();

	m_pNode = ParallaxNode::create();
	this->addChild(m_pNode);
}

void ParallaxLayer::cleanParallax()
{
	if (m_pNode != nullptr)
	{
		m_pNode->removeFromParentAndCleanup(true);
		m_pNode = nullptr;
	}
}

void ParallaxLayer::addParallaxElement(Sprite* _tex, Point &_pos, Point &_parallaxRatio, int _order)
{
	if (m_pNode == nullptr) initParallax();

	m_pNode->addChild(_tex, _order, _parallaxRatio, _pos);
}