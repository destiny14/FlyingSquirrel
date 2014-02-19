#include "LevelTestScene.h"

USING_NS_CC;

Scene* LevelTestScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	auto layer = LevelTestScene::create();
	
	// 'layer' is an autorelease object
	
	// add layer as a child to scene
	scene->addChild(layer);
	Level* l = Level::loadLevel("tmpname.xml");

	auto mainlayer = l->getMainLayer();

	//MainLayer* mainlayer = l->getMainLayer();
	scene->addChild(mainlayer);

	//scene->addChild(layer2);

	// return the scene
	return scene;
}

LevelTestScene::LevelTestScene()
{

}

LevelTestScene::~LevelTestScene()
{

}

bool LevelTestScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void LevelTestScene::update(float dt)
{

}

void LevelTestScene::draw()
{

}