#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Player.h"
#include "..\Components\Collider.h"

Player* Player::create(char* filename, MainLayer* parent)
{
	Player* player = new Player();
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		player->setTexture(tex);
		player->setCollider();
		player->setParent(parent);
		player->setGround(false);
		return player;
	}
	return nullptr;
}

Player::Player() {}

Player::~Player() {}

Player* Player::create(InputManager* pManager)
{
	Player* player = new Player;

	EventKeyboard::KeyCode keysForward[] = { EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW };
	EventKeyboard::KeyCode keysBackward[] = { EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW };
	EventKeyboard::KeyCode keysJump[] = { EventKeyboard::KeyCode::KEY_SPACE, EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW };

	player->m_pForward = pManager->createKeyboardAction(keysForward, 2, "Forward");
	player->m_pBackward = pManager->createKeyboardAction(keysBackward, 2, "Backward");
	player->m_pJump = pManager->createKeyboardAction(keysJump, 3, "Jump");

	return player;
}

bool Player::init()
{
	m_isGrounded = true;

	return true;
}

void Player::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	PlayerCollider* collider = PlayerCollider::create(boundingBox.size.width, boundingBox.size.height);
	this->addComponent(collider);
}

//void Player::updateCollider()
//{
//	Rect oldCollider = getLeftCollider();
//	setLeftCollider(oldCollider.size.width, oldCollider.size.height);
//	oldCollider = getRightCollider();
//	setRightCollider(oldCollider.size.width, oldCollider.size.height);
//	oldCollider = getBottomCollider();
//	setBottomCollider(oldCollider.size.width, oldCollider.size.height);
//	float y = getPositionY();
//	Rect bb = getSprite()->getBoundingBox();
//}

PlayerCollider* Player::getPlayerColliderComponent()
{
	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
}


void Player::update(float dt)
{
	Moveable::update(dt, true);
	PlayerCollider* p = getPlayerColliderComponent();
	if (p != nullptr)
		p->update(dt);

	/*if (m_pForward->isPressed && m_isGrounded)
	{
		//getOwner()->setPositionX = getOwner()->getPositionX + 1.0f;
	}
	if (m_pBackward->isPressed && m_isGrounded)
	{
		//getOwner()->setPositionX = getOwner()->getPositionX - 1.0f;
	}
	if (m_pJump->isPressed && m_isGrounded)
	{
		//getOwner()->setPositionY = getOwner()->getPositionY + 6.0f;
		//m_isGrounded = false;
	}
	if (m_pJump->isPressed && !m_isGrounded)
	{
		// ?!
	}*/
	
	CheckForCollisions();
}

void Player::CheckForCollisions()
{
	list<Ground*> physObj = getParent()->getPhysicsObjects();
	for (Ground* g : physObj)
	{
		if (g->getGround() == true)
		{
			Collider* c = g->getColliderComponent();
			if (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
			{
				// kollision (boden)
				setGrounded(true);
			}
		}
	}
}