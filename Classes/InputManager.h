#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "cocos2d.h"
#include "InputAction.h"

USING_NS_CC;

class InputManager
{
public:
	InputManager(Node* _pNode);
	~InputManager(void);

	/*
	*	Erzeugt eine neue Action mit gegebenem Namen, und KeyCode
	*/
	InputAction* createKeyboardAction(EventKeyboard::KeyCode _code, char* _pName);
	/*
	*	NYI
	*/
	InputAction* createMouseAction(char* _name);
	
	/*
	*	Muss jedes Frame aufgerufen werden
	*/
	void update();
	/*Internal*/
	void onKeyPressed(EventKeyboard::KeyCode _keyCode, Event* _event);
	/*Internal*/
	void onKeyReleased(EventKeyboard::KeyCode _keyCode, Event* _event);
	/*Internal*/
	bool isKeyPressed(EventKeyboard::KeyCode _keyCode);
private:
	Node* m_pNode;
	EventListenerKeyboard* m_keyL;
	std::list<InputAction*> m_actions;
	bool* m_keyPressed;
};

#endif