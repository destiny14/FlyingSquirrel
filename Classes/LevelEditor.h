#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include "cocos2d.h"

USING_NS_CC;

class LevelEditor : public Layer
{
public:
	static Scene* createScene();
	LevelEditor();
	~LevelEditor();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();

	void addTextureObjectCallback(Object* sender);

	CREATE_FUNC(LevelEditor);
};


#endif // !__LEVELEDITOR_H__
