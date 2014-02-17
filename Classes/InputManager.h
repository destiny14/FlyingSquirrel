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
	InputAction* createKeyboardAction(EventKeyboard::KeyCode* _code, int length, char* _pName);
	/*
	*	Erzeugt eine neue (Mouse)Action mit gegebenem Namen
	*/
	MouseInputAction* createMouseAction(char* _name);
	
	/*
	*	Muss jedes Frame aufgerufen werden
	*/
	void update();
	/*Internal*/
	void onMouseMove(Event* _event);
	/*Internal*/
	void onMouseDown(Event* _event);
	/*Internal*/
	void onMouseUp(Event* _event);
	/*Internal*/
	void onKeyPressed(EventKeyboard::KeyCode _keyCode, Event* _event);
	/*Internal*/
	void onKeyReleased(EventKeyboard::KeyCode _keyCode, Event* _event);
	/*Internal*/
	bool isKeyPressed(EventKeyboard::KeyCode _keyCode);
	/*Internal*/
	Point getMousePosition();
	bool isMouse1Pressed();
private:
	Point m_mousePosition;
	Node* m_pNode;
	EventListenerKeyboard* m_keyL;
	EventListenerMouse* m_mouseL;
	std::list<InputAction*> m_actions;
	bool* m_keyPressed;
	bool m_mouse1Pressed;
};

#endif