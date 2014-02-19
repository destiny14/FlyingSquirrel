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

KeyboardInputAction::KeyboardInputAction(char* name, cocos2d::EventKeyboard::KeyCode* code, int _length) : InputAction(name)
{
	m_length = 0;
	this->changeKeyCode(code, _length);
}

KeyboardInputAction::~KeyboardInputAction(void)
{
	InputAction::~InputAction();
}

void KeyboardInputAction::changeKeyCode(const EventKeyboard::KeyCode* code, int length)
{
	m_length = length;
	m_code = new EventKeyboard::KeyCode[length];
	memcpy(m_code, code, sizeof(EventKeyboard::KeyCode) * length);
}

void KeyboardInputAction::check(InputManager* _manager)
{
	bool pressed = false;

	for (int i = 0; i < m_length; i++)
		pressed = (pressed || (_manager->isKeyPressed(m_code[i])));

	if (pressed)
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

MouseInputAction::MouseInputAction(char* _name, int _button) : InputAction(_name)
{
	button = _button;
}

MouseInputAction::~MouseInputAction()
{
	InputAction::~InputAction();
}

void MouseInputAction::check(InputManager* _manager)
{
	bool pressed = _manager->isMousePressed(button);

	m_mousePos = _manager->getMousePosition();

	if (pressed)
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