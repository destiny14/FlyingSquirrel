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

	Texture* tex = Texture::create(filename);

	if (tex)
	{
		player->setTexture(tex);
		//player->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 163.0f, 243.0f)); // Stand
		player->setCollider();
		player->setParent(parent);
		player->setGround(false);

		player->init();

		return player;
	}
	return nullptr;
}

Player::Player() {}

Player::~Player() {}

bool Player::init()
{
	m_sawyerRunFrame = 0;
	m_movement = None;
	m_direction.x = 0.0f;
	m_direction.y = 0.0f;
	m_speed = 10.0f;
	m_jump = false;
	m_doubleJump = false;
	m_readyToFly = false;
	m_isFlying = false;

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("sawyer.plist");
	m_pSpriteBatch = SpriteBatchNode::create("sawyer.png");

	////////////////////////
	// Stehen - Animation //
	////////////////////////
	for (int i = 0; i < 31; i++)
	{
		filename = String::createWithFormat("skeleton-Stand%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pStandFrames = Animation::createWithSpriteFrames(frames, 0.065f);
	m_pStandAction = RepeatForever::create(Animate::create(m_pStandFrames));
	m_pStandAction->setTag(0);
	m_pStandFrames->retain();
	frames.clear();

	///////////////////////
	// Gehen - Animation //
	///////////////////////
	for (int i = 0; i < 31; i++)
	{
		filename = String::createWithFormat("skeleton-Run%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pRunFrames = Animation::createWithSpriteFrames(frames, 0.0275f);
	m_pRunFrames->retain();
	frames.clear();

	//////////////////////////
	// Springen - Animation //
	//////////////////////////
	for (int i = 0; i < 43; i++)
	{
		filename = String::createWithFormat("skeleton-Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pJumpFrames = Animation::createWithSpriteFrames(frames, 0.03f);
	m_pJumpFrames->retain();
	frames.clear();

	//////////////////////
	// Flug - Animation //
	//////////////////////
	for (int i = 0; i < 21; i++)
	{
		filename = String::createWithFormat("skeleton-Flug%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pFlightFrames = Animation::createWithSpriteFrames(frames, 0.035f);
	m_pFlightFrames->retain();
	frames.clear();

	////////////////////////
	// Landen - Animation //
	////////////////////////
	for (int i = 42; i < 69; i++)
	{
		filename = String::createWithFormat("skeleton-Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pLandingFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pLandingFrames->retain();
	frames.clear();

	this->getSprite()->runAction(m_pStandAction);

	return true;
}

void Player::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	PlayerCollider* collider = PlayerCollider::create(160.0f, 250.0f);//boundingBox.size.width, boundingBox.size.height);
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

	if (m_pForward->wasPressed())
		m_movement = (EMovement)(m_movement | EMovement::Right);
	if (m_pBackward->wasPressed())
		m_movement = (EMovement)(m_movement | EMovement::Left);
	if (m_pJump->wasPressed())
		m_movement = (EMovement)(m_movement | EMovement::Jump);

	if (m_pForward->wasReleased())
		m_movement = (EMovement)(m_movement ^ EMovement::Right);
	if (m_pBackward->wasReleased())
		m_movement = (EMovement)(m_movement ^ EMovement::Left);
	if (m_pJump->wasReleased())
		m_movement = (EMovement)(m_movement ^ EMovement::Jump);

	m_direction.x = 0.0f;
	setVelocityX(0.0f);

	///////////////////////
	// Stehen - Bewegung //
	///////////////////////
	if (!m_pForward->isPressed() && !m_pBackward->isPressed() && !m_pJump->isPressed())
	{
		if (!this->getSprite()->getActionByTag(0) && this->getGrounded())
		{
			this->getSprite()->stopAllActions();
			m_pStandAction = RepeatForever::create(Animate::create(m_pStandFrames));
			m_pStandAction->setTag(0);
			this->getSprite()->runAction(m_pStandAction);
		}
	}
	///////////////////////
	// Landen - Bewegung //
	///////////////////////
	if (m_pJump->wasReleased() && m_isFlying || this->getGrounded() && m_jump)
	{
		this->getSprite()->stopAllActions();
		m_pLandingAction = Repeat::create(Animate::create(m_pLandingFrames), 1);
		m_pLandingAction->setTag(4);
		this->getSprite()->runAction(m_pLandingAction);
		m_jump = false;
		m_doubleJump = false;
		m_readyToFly = false;
		m_isFlying = false;
	}
	/////////////////////////
	// Springen - Bewegung //
	/////////////////////////
 	else if (m_pJump->wasPressed() && this->getGrounded())
	{
		addVelocity(0.0f, 300.0f);
		this->setGrounded(false);
		m_jump = true;
		if (!this->getSprite()->getActionByTag(2))
		{
			this->getSprite()->stopAllActions();
			m_pJumpAction = Repeat::create(Animate::create(m_pJumpFrames), 1);
			m_pJumpAction->setTag(2);
			this->getSprite()->runAction(m_pJumpAction);
		}
	}
	/////////////////////////////
	// Doppelsprung - Bewegung //
	/////////////////////////////
	else if (m_pJump->wasPressed() && !(this->getGrounded()) && !m_doubleJump && m_jump)
	{
		addVelocity(0.0f, 200.0f);
		m_doubleJump = true;
		m_readyToFly = false;
	}
	////////////////////////
	// Fliegen - Bewegung //
	////////////////////////
	else if (m_pJump->wasReleased() && !m_isFlying && m_doubleJump)
	{
		m_readyToFly = true;
	}
	else if (m_pJump->isPressed() && m_doubleJump && m_readyToFly)
	{
   		if (!this->getSprite()->getActionByTag(3))
		{
			this->getSprite()->stopAllActions();
			m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			this->getSprite()->runAction(m_pFlightAction);
		}

		m_isFlying = true;
		addVelocity((400.0f * this->getSprite()->getScaleX()), 2.0f);
	}
	////////////////////////////////
	// Rückwärts Gehen - Bewegung //
	////////////////////////////////
	if (m_movement & EMovement::Left)
	{
		m_direction.x = -1.0f;

		if (!this->getSprite()->getActionByTag(1) && this->getGrounded())
		{
			this->getSprite()->stopAllActions();
			m_pRunAction = RepeatForever::create(Animate::create(m_pRunFrames));
			m_pRunAction->setTag(1);
			this->getSprite()->runAction(m_pRunAction);
		}
		this->getSprite()->setScaleX(-1.0f);
	}
	///////////////////////////////
	// Vorwärts Gehen - Bewegung //
	///////////////////////////////
	if (m_movement & EMovement::Right)
	{
		m_direction.x += 1.0f;

		if (!this->getSprite()->getActionByTag(1) && this->getGrounded())
		{
			this->getSprite()->stopAllActions();
			m_pRunAction = RepeatForever::create(Animate::create(m_pRunFrames));
			m_pRunAction->setTag(1);
			this->getSprite()->runAction(m_pRunAction);
		}
		this->getSprite()->setScaleX(1.0f);
	}
	if (!this->getGrounded() && !m_jump)
	{
		if (!this->getSprite()->getActionByTag(3))
		{
			this->getSprite()->stopAllActions();
			m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			this->getSprite()->runAction(m_pFlightAction);
		}
	}

	m_direction.x *= m_speed;
	this->setPosition(this->getPosition() + m_direction);

	//static float timeForHit = 0.075f;

	CheckForCollisions();
}

void Player::CheckForCollisions()
{
	setGrounded(false);
	list<Ground*>* physObj = getParent()->getPhysicsObjects();
	for (Ground* g : *physObj)
	{
		if (g->getGround() == true)
		{
			bool hack = false;
			Collider* c = g->getColliderComponent();
			while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
			{
				hack = true;
				// kollision (boden)
				setGrounded(true);
				setPositionY(getPositionY() + 0.01f);
				getPlayerColliderComponent()->update(0.0f);
			}
			if (hack)
			{
				setPositionY(getPositionY() - 0.01f);
				getPlayerColliderComponent()->update(0.0f);
			}

			while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getLeftCollider()))
			{
				//Collision left wand
				setPositionX(getPositionX() + 0.01f);
				getPlayerColliderComponent()->update(0.0f);
			}
			while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getRightCollider()))
			{
				//Collision right wand
				setPositionX(getPositionX() - 0.01f);
				getPlayerColliderComponent()->update(0.0f);
			}
		}
	}
}