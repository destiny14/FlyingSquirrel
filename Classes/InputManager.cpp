#include "InputManager.h"

InputManager::InputManager(Scene* _scene)
{
	m_keyPressed = new bool[(int) EventKeyboard::KeyCode::KEY_SEARCH];
	m_keyL = EventListenerKeyboard::create();
	m_keyL->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	m_keyL->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyL, _scene);
}

InputManager::~InputManager()
{
	delete m_keyPressed;
	delete m_keyL;
	while (!m_actions.empty())
	{
		InputAction* pAction = m_actions.front();
		m_actions.remove(pAction);
		delete pAction;
	}
}

InputAction* InputManager::createKeyboardAction(EventKeyboard::KeyCode _code, char* _name)
{
	KeyboardInputAction* pAction = new KeyboardInputAction(_code, _name);

	m_actions.push_front(pAction);

	return pAction;
}

InputAction* InputManager::createMouseAction(char* _name)
{
	return nullptr;
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode _keyCode, Event* _event)
{
	m_keyPressed[(int)_keyCode] = true;
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode _keyCode, Event* _event)
{
	m_keyPressed[(int)_keyCode] = false;
}

bool InputManager::isKeyPressed(EventKeyboard::KeyCode _keyCode)
{
	return m_keyPressed[(int)_keyCode];
}