#include "InputAction.h"
#include "InputManager.h"

InputAction::InputAction(char* _name)
{
	m_name = _name;
	m_timesPressed = 0;
	m_released = false;
	m_pressed = false;
}

InputAction::~InputAction()
{

}

void InputAction::check(InputManager* _manager)
{

}

void InputAction::resetFrame()
{
	//If the Action was released last Frame
	if (m_released)
	{
		//then reset the counter
		m_timesPressed = 0;
	}
	//reset pressed and released
	m_pressed = false;
	m_released = false;
}

KeyboardInputAction::KeyboardInputAction(cocos2d::EventKeyboard::KeyCode code, char* name) : InputAction(name)
{
	this->changeKeyCode(code);
}

KeyboardInputAction::~KeyboardInputAction(void)
{
	InputAction::~InputAction();
}

void KeyboardInputAction::check(InputManager* _manager)
{
	if (_manager->isKeyPressed(m_code))
	{
		m_pressed = true;
		m_timesPressed++;
	}
	
	if (m_timesPressed > 1) //Was recently pressed  
	{
		if (m_pressed) //was pressed this frame
			m_pressed = false;	//set to false, to indicate this was not the first press
		else
			m_released = true;	//set to true, to indicate, this was the last press
	}
}