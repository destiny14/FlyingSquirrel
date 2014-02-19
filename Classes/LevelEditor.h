#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include "cocos2d.h"
#include "InputAction.h"
#include "InputManager.h"
#include "Levelsystem\Level.h"
#include <string>

USING_NS_CC;

using namespace std;

class LevelEditor : public Layer
{
public:
	Menu* MainMenu;
	Menu* ChooseFileMenu;
	Menu* ChooseFileNavMenu;

	static Scene* createScene();
	LevelEditor();
	~LevelEditor();

	virtual bool init();
	virtual void update(float dt);
	virtual void draw();

	void addTextureObjectCallback(Object* sender);
	void addGroundObjectCallback(Object* sender);
	void chooseFileCallback(Object* sender, string file, int levelType);
	void moveFileSelectUpCallback();
	void moveFileSelectDownCallback();
	void changeLayerCallback();
	void saveLevelCallback();
	void toggleGridCallback();

	CREATE_FUNC(LevelEditor);
private:
	Texture* m_currentSelected;
	bool m_snapToGrid;
	Level* m_pLevel;
	InputManager* m_pInput;
	MouseInputAction* m_mouseInputAction;
	Node* m_pCurrentMoving;
	Size m_visibleSize;
	Sprite* m_pBackgroundSprite;
	Point m_lastMousePos;
};

#endif // !__LEVELEDITOR_H__
