#include "InputManager.h"

InputManager::InputManager(Node* _pNode)
{
	m_pNode = _pNode;
	m_mousePosition = Point(0, 0);

	m_keyPressed = new bool[(int) EventKeyboard::KeyCode::KEY_SEARCH + 1];
	for (int i = 0; i < (int)EventKeyboard::KeyCode::KEY_SEARCH + 1; ++i)
		m_keyPressed[i] = false;

	m_keyL = EventListenerKeyboard::create();
	m_mouseL = EventListenerMouse::create();
	m_mouse1Pressed = false;
	m_mouseL->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	m_mouseL->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	m_mouseL->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);

	m_keyL->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	m_keyL->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	m_pNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyL, m_pNode);
	m_pNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_mouseL, m_pNode);
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

MouseInputAction* InputManager::createMouseAction(char* _name)
{
	MouseInputAction* pAction = new MouseInputAction(_name);
	m_actions.push_front(pAction);
	return pAction;
}

void InputManager::onMouseMove(Event* _event)
{
	EventMouse* eMouse = dynamic_cast<EventMouse*>(_event);
	m_mousePosition.x = eMouse->getCursorX() / EGLView::getInstance()->getScaleX();
	m_mousePosition.y = eMouse->getCursorY() / EGLView::getInstance()->getScaleY();
	
}

void InputManager::onMouseDown(Event* _event)
{
	EventMouse* eMouse = dynamic_cast<EventMouse*>(_event);

	if (eMouse->getMouseButton() == 0)
	{
		m_mouse1Pressed = true;
	}
	if (eMouse->getMouseButton() == 1)
	{
		m_mouse2Pressed = true;
	}
}

void InputManager::onMouseUp(Event* _event)
{
	m_mouse1Pressed = false;
	m_mouse2Pressed = false;
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

bool InputManager::isMouse1Pressed()
{
	return m_mouse1Pressed;
}

bool InputManager::isMouse2Pressed()
{
	return m_mouse2Pressed;
}

Point InputManager::getMousePosition()
{
	return m_mousePosition;
}