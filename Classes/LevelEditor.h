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

	static Scene* createScene(char* filename = "");
	LevelEditor();
	~LevelEditor();

	virtual bool init(char* filename = "");
	virtual void update(float dt);
	virtual void draw();

	void addTextureObjectCallback(Object* sender);
	void addGroundObjectCallback(Object* sender);
	void addNutObjectCallback(Object* sender);
	void addCrystalObjectCallback(Object* sender);
	void addAirObjectCallback(Object* sender);
	void chooseFileCallback(Object* sender, string file, int levelType);
	void moveFileSelectUpCallback();
	void moveFileSelectDownCallback();
	void changeLayerCallback();
	void saveLevelCallback();
	void toggleGridCallback();
	void toggleSelectionMode();
	void mainMenuCallback();

	static LevelEditor* create(char* filename);
private:
	Sprite* m_PlayerSpawner;
	bool m_selectionMode;
	Texture* m_currentSelected;
	bool m_snapToGrid;
	Level* m_pLevel;
	InputManager* m_pInput;
	MouseInputAction* m_mouseInputAction;
	MouseInputAction* m_mouseInputAction2;
	InputAction* m_deleteObjectInputAction;
	Node* m_pCurrentMoving;
	Size m_visibleSize;
	Sprite* m_pBackgroundSprite;
	Point m_lastMousePos;
	Ground* m_currentSelectedGround;
};

#endif // !__LEVELEDITOR_H__
