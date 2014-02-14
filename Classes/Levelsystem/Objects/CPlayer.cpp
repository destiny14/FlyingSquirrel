#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Player.h"
#include "..\Components\Collider.h"

Player* Player::create(char* filename, MainLayer* parent, InputManager* pManager)
{
	Player* player = new Player();

	EventKeyboard::KeyCode keysForward[] = { EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW };
	EventKeyboard::KeyCode keysBackward[] = { EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW };
	EventKeyboard::KeyCode keysJump[] = { EventKeyboard::KeyCode::KEY_SPACE, EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW };

	player->m_pForward = pManager->createKeyboardAction(keysForward, 2, "Forward");
	player->m_pBackward = pManager->createKeyboardAction(keysBackward, 2, "Backward");
	player->m_pJump = pManager->createKeyboardAction(keysJump, 3, "Jump");

	player->init();

	Texture* tex = Texture::create(filename);

	if (tex)
	{
		player->setTexture(tex);
		player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 264.0f, 270.0f)); //Run
		//player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 283.0f, 272.0f)); // Jump
		//player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 214.0f, 256.0f)); // Hit
		//player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 163.0f, 243.0f)); // Stand
		player->setCollider();
		player->setParent(parent);
		player->setGround(false);

		return player;
	}
	return nullptr;
}

Player::Player() {}

Player::~Player() {}

bool Player::init()
{
	m_sawyerRunFrame = 0;

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

	/*static float timeForHit = 0.075f;
	if (true)
	{
		timeForHit -= dt;
	}
	if (timeForHit < 0)
	{
		// change frame
		++m_sawyerRunFrame;
		if (m_sawyerRunFrame > 5)
		{
			m_sawyerRunFrame = 0;
		}

		this->getSprite()->setTextureRect(Rect(m_sawyerRunFrame % 6 * 214, m_sawyerRunFrame / 6 * 256, 214, 256));
		timeForHit += 0.075f;
	}*/

	/*static float timeForStand = 0.065f;
	if (true)
	{
		timeForStand -= dt;
	}
	if (timeForStand < 0)
	{
		// change frame
		++m_sawyerRunFrame;
		if (m_sawyerRunFrame > 30)
		{
			m_sawyerRunFrame = 0;
		}

		this->getSprite()->setTextureRect(Rect(m_sawyerRunFrame % 12 * 163, m_sawyerRunFrame / 12 * 243, 163, 243));
		timeForStand += 0.065f;
	}*/
	static float timeForRun = 0.0275f;
	if (true)
	{
		timeForRun -= dt;
	}
	if (timeForRun < 0)
	{
		// change frame
		++m_sawyerRunFrame;
		if (m_sawyerRunFrame > 30)
		{
			m_sawyerRunFrame = 0;
		}

		this->getSprite()->setTextureRect(Rect(m_sawyerRunFrame % 7 * 264, m_sawyerRunFrame / 7 * 270, 264, 270));
		timeForRun += 0.0275f;
	}
	log("%i", m_pForward->isPressed());
	if (m_pForward->isPressed() && this->getGrounded())
	{
		log("ich kann humpeln");
		this->setPositionX(this->getPositionX() + 1.0f);
	}
	if (m_pBackward->isPressed() && this->getGrounded())
	{
		this->setPositionX(this->getPositionX() - 1.0f);
	}
	if (m_pJump->isPressed() && this->getGrounded())
	{
		static float timeForJump = 0.03f;
		if (true)
		{
			timeForJump -= dt;
		}
		if (timeForJump < 0)
		{
			// change frame
			++m_sawyerRunFrame;
			if (m_sawyerRunFrame > 45)
			{
				m_sawyerRunFrame = 0;
			}

			this->getSprite()->setTextureRect(Rect(m_sawyerRunFrame % 14 * 283, m_sawyerRunFrame / 14 * 272, 283, 272));
			timeForJump += 0.03f;
		}
		this->setPositionY(this->getPositionY() + 6.0f);
		this->setGrounded(false);
	}
	if (m_pJump->isPressed() && !this->getGrounded())
	{
		this->setPositionY(this->getPositionY() + 4.0f);
	}
	
	CheckForCollisions();
}

void Player::CheckForCollisions()
{
	list<Ground*>* physObj = getParent()->getPhysicsObjects();
	for (Ground* g : *physObj)
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