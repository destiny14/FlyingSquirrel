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
		//player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 214.0f, 256.0f)); // Hit
		player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 163.0f, 243.0f)); // Stand
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
	m_pState = "stand";

	m_pStand = Texture::create("sawyerstand.png");
	m_pRun = Texture::create("sawyerrun.png");
	m_pJumpTex = Texture::create("sawyerjump.png");
	m_pHit = Texture::create("sawyerhit.png");

	m_pStand->retain();
	m_pRun->retain();
	m_pJumpTex->retain();
	m_pHit->retain();

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
	
	if (m_pForward->isPressed() && this->getGrounded())
	{
		static float timeForRun = 0.0275f;
		if (strcmp(m_pState, "runForward") != 0)
		{
			this->setTexture(m_pRun);
			this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 264.0f, 270.0f));
			this->getSprite()->setScale(1.0f);
			m_pState = "runForward";
		}
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
		this->setPositionX(this->getPositionX() + 1.0f);
	}
	else if (m_pBackward->isPressed() && this->getGrounded())
	{
		static float timeForRun = 0.0275f;
		if (strcmp(m_pState, "runBackward") != 0)
		{
			this->setTexture(m_pRun);
			this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 264.0f, 270.0f));
			this->getSprite()->setScale(-1.0f);
			m_pState = "runBackward";
		}
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
		this->setPositionX(this->getPositionX() - 1.0f);
	}
	else if (m_pJump->isPressed() && this->getGrounded())
	{
		static float timeForJump = 0.03f;
		if (strcmp(m_pState, "jump") != 0)
		{
			this->setTexture(m_pJumpTex);
			this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 283.0f, 272.0f));
			m_pState = "jump";
		}
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
	else
	{
		static float timeForStand = 0.065f;
		if (strcmp(m_pState, "stand") != 0)
		{
			this->setTexture(m_pStand);
			this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 163.0f, 243.0f));
			m_pState = "stand";
		}
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
		}
	}
	/*if (m_pJump->isPressed() && !this->getGrounded())
	{
		this->setPositionY(this->getPositionY() + 4.0f);
	}*/

	log("%s", m_pState);

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