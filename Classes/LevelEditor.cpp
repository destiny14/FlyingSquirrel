#include "LevelEditor.h"
#include "UI.h"

Scene* LevelEditor::createScene()
{
	auto scene = Scene::create();

	auto layer = LevelEditor::create();

	scene->addChild(layer);
	return scene;
}

LevelEditor::LevelEditor() {}
LevelEditor::~LevelEditor() {}

bool LevelEditor::init()
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	ACTIVATELEVELEDITORUI(this);
	this->scheduleUpdate();
	return true;
}

void LevelEditor::addTextureObjectCallback(Object* sender)
{

}

void LevelEditor::update(float dt)
{
	UPDATEUI;
}

void LevelEditor::draw()
{

}