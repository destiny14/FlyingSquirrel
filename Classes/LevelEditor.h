#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include "cocos2d.h"
#include "InputAction.h"
#include "InputManager.h"
#include <string>

USING_NS_CC;

using namespace std;

class LevelEditor : public Layer
{
public:
	Menu* ChooseFileMenu;

	static Scene* createScene();
	LevelEditor();
	~LevelEditor();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();

	void addTextureObjectCallback(Object* sender);
	void addGroundObjectCallback(Object* sender);
	void chooseFileCallback(Object* sender, string file);
	void moveFileSelectUpCallback();
	void moveFileSelectDownCallback();

	CREATE_FUNC(LevelEditor);
private:
	InputManager* m_pInput;
	MouseInputAction* m_mouseInputAction;
	Node* m_pCurrentMoving;
	Size m_visibleSize;
	Sprite* m_pBackgroundSprite;
};

#endif // !__LEVELEDITOR_H__
