#include "InputManager.h"

InputManager::InputManager(Node* _pNode)
{
	m_pNode = _pNode;

	m_keyPressed = new bool[(int) EventKeyboard::KeyCode::KEY_SEARCH];

	m_keyL = EventListenerKeyboard::create();

	m_keyL->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	m_keyL->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	m_pNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyL, m_pNode);
}

InputManager::~InputManager()
{
	m_pNode->getEventDispatcher()->removeEventListener(m_keyL);
	
	while (!m_actions.empty())
	{
		InputAction* pAction = m_actions.front();
		m_actions.remove(pAction);
		delete pAction;
	}

	delete m_keyL;
	delete m_keyPressed;
	m_pNode = nullptr;
}

void InputManager::update()
{
	for each (InputAction* pAction in m_actions)
	{
		pAction->resetFrame();
		pAction->check(this);
	}
}

InputAction* InputManager::createKeyboardAction(EventKeyboard::KeyCode* _code, int _length, char* _name)
{
	KeyboardInputAction* pAction = new KeyboardInputAction(_name, _code, _length);

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
	return m_keyPressed[(int)(_keyCode)];
}