#include "LevelTestScene.h"

USING_NS_CC;

Scene* LevelTestScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	auto layer = LevelTestScene::create();
	auto layer2 = MainLayer::create();
	
	// 'layer' is an autorelease object
	
	// add layer as a child to scene
	scene->addChild(layer);
	scene->addChild(layer2);

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

	Level* l = Level::loadLevel("testlevel.xml");

	auto mainlayer = MainLayer::create();

	//MainLayer* mainlayer = l->getMainLayer();
	addChild(mainlayer);
	return true;
}

void LevelTestScene::update(float dt)
{

}

void LevelTestScene::draw()
{

}