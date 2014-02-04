#ifndef __INPUTACTION_H__
#define __INPUTACTION_H__

#include "cocos2d.h"

USING_NS_CC;

class InputManager;

class InputAction
{
public:
	InputAction(char* name);
	virtual ~InputAction(void);
	/*
	*	Gibt den Namen der Aktion zurueck
	*/
	char* getName() { return m_name; }
	/*
	*	Gibt zurueck ob die Taste gedrueckt wird
	*/
	bool isPressed() { return m_timesPressed > 0; }
	/*
	*	Gibt zurueck, wie lange die Taste gedrückt wurde (in Frames)
	*/
	int getConsecutivePresses() { return m_timesPressed; }
	/*
	*	Gibt zurück ob die Taste losgelassen wurde
	*/
	bool wasReleased() { return m_released; }
	/*
	*	Gibt zurück ob die Taste gedrueckt wurde
	*/
	bool wasPressed() { return m_pressed; }

	/*Internal*/
	void resetFrame();
	/*Internal*/
	virtual void check(InputManager* _manager);
protected:
	bool m_released;
	bool m_pressed;
	int m_timesPressed;
private:
	char* m_name;
};

class KeyboardInputAction : public InputAction
{
public:
	KeyboardInputAction(char* name, EventKeyboard::KeyCode* code, int length);
	virtual ~KeyboardInputAction(void);
	/*Internal*/
	virtual void check(InputManager* _manager);
	/*
	*	Wechselt den KeyCode
	*/
	void changeKeyCode(const EventKeyboard::KeyCode* code, int length);
private:
	EventKeyboard::KeyCode* m_code;
	int m_length;
};

//NYI
class MouseInputAction : public InputAction {
public:

	int getX() { return m_x; }
	int getY() { return m_y; }
private:
	int m_x;
	int m_y;
};

#endif