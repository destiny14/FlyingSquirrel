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
	EventKeyboard::KeyCode keysShoot[] = { EventKeyboard::KeyCode::KEY_SHIFT, EventKeyboard::KeyCode::KEY_RETURN , EventKeyboard::KeyCode::KEY_KP_ENTER };

	player->m_pForward = pManager->createKeyboardAction(keysForward, 2, "Forward");
	player->m_pBackward = pManager->createKeyboardAction(keysBackward, 2, "Backward");
	player->m_pJump = pManager->createKeyboardAction(keysJump, 3, "Jump");
	player->m_pShoot = pManager->createKeyboardAction(keysShoot, 3, "Shoot");

	Texture* tex = Texture::create(filename);

	if (tex)
	{
		player->setTexture(tex);
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
	Shooter* shooter = Shooter::create(this->getTexture()->getFilename(), this->getParent());

	m_health = 3;
	m_nuts = 0;

	m_counterDeath = 0;
	m_counterToShoot = 0;

	m_sawyerRunFrame = 0;
	m_movement = None;
	m_direction.x = 0.0f;
	m_direction.y = 0.0f;
	m_speed = 10.0f;
	m_jump = false;
	m_doubleJump = false;
	m_readyToFly = false;
	m_isFlying = false;
	m_rescueFly = false;
	m_isDead = false;
	m_shooted = false;
	m_readyToFall = false;
	m_topCollision = false;
	m_bottomColWhileTopCol = false;
	m_topCollisionGround = nullptr;

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("sawyer.plist");
	m_pSpriteBatch = SpriteBatchNode::create("sawyer.png");

	////////////////////////
	// Stehen - Animation // // 0
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
	// Gehen - Animation // // 1
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
	// Springen - Animation // // 2
	//////////////////////////
	for (int i = 0; i < 43; i++)
	{
		filename = String::createWithFormat("skeleton-Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pJumpFrames = Animation::createWithSpriteFrames(frames, 0.01f);
	m_pJumpFrames->retain();
	frames.clear();
	//////////////////////
	// Flug - Animation // // 3
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
	// Landen - Animation // // 4
	////////////////////////
	for (int i = 42; i < 69; i++)
	{
		filename = String::createWithFormat("skeleton-Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pLandingFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pLandingFrames->retain();
	frames.clear();
	/////////////////////
	// Hit - Animation // // 5
	/////////////////////
	for (int i = 0; i < 9; i++)
	{
		filename = String::createWithFormat("skeleton-Hit%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pHitFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pHitFrames->retain();
	frames.clear();
	/////////////////////
	// Tot - Animation // // 6
	/////////////////////
	for (int i = 0; i < 24; i++)
	{
		filename = String::createWithFormat("skeleton-Dead%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pDeathFrames->retain();
	frames.clear();
	////////////////////////
	// Schuss - Animation // // 7
	////////////////////////
	for (int i = 0; i < 22; i++)
	{
		filename = String::createWithFormat("skeleton-Shot%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pShootFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pShootFrames->retain();
	frames.clear();
	////////////////////////////////
	// Falleinleitung - Animation // // 8
	////////////////////////////////
	for (int i = 0; i < 4; i++)
	{
		filename = String::createWithFormat("skeleton-Fall_Einleitung%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pFallStartFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pFallStartFrames->retain();
	frames.clear();
	//////////////////////
	// Fall - Animation // // 9
	//////////////////////
	for (int i = 0; i < 6; i++)
	{
		filename = String::createWithFormat("skeleton-Fall%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pFallFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pFallFrames->retain();
	frames.clear();
	///////////////////////////
	// FallToFly - Animation // // 10
	///////////////////////////
	for (int i = 0; i < 6; i++)
	{
		filename = String::createWithFormat("skeleton-Flug_Einleitung%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pFallToFlyFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pFallToFlyFrames->retain();
	frames.clear();

	this->getSprite()->runAction(m_pStandAction);

	return true;
}

void Player::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	PlayerCollider* collider = PlayerCollider::create(160.0f, 250.0f);
	this->addComponent(collider);
}

PlayerCollider* Player::getPlayerColliderComponent()
{
	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
}

void Player::update(float dt)
{
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

	if (this->getSprite()->getActionByTag(5))
	{
		m_movement = None;
		return;
	}
	PlayerCollider* p = getPlayerColliderComponent();
	if (p != nullptr)
		p->update(dt);
	Shooter::update(dt, true);
	
	m_direction.x = 0.0f;
	setVelocityX(0.0f);

	////////////////////////////////
	// Tod - Bewegung - SPIELENDE //
	////////////////////////////////
	if (m_health > 0)
	{
		CheckForCollisions();
	}
	else if (m_health <= 0 && !m_isDead)
	{
		addVelocity((-750.0f * this->getScaleX()), -300.0f);
		if (m_counterDeath == 0)
		{
			this->getSprite()->stopAllActions();
			m_pDeathAction = Repeat::create(Animate::create(m_pDeathFrames), 1);
			m_pDeathAction->setTag(6);
			this->getSprite()->runAction(m_pDeathAction);
		}
		if (m_counterDeath == 23)
		{
			m_isDead = true;
		}
		m_counterDeath++;
		return;
	}
	else if (m_health <= 0 && m_isDead)
	{
		addVelocity(0.0f, -500.0f);
		return;
	}
	/////////////////////////
	// Schießen - Bewegung //
	/////////////////////////
	if (m_pShoot->wasPressed())// && this->getGrounded())
	{
		this->getSprite()->stopAllActions();
		m_pShootAction = Repeat::create(Animate::create(m_pShootFrames), 1);
		m_pShootAction->setTag(7);
		this->getSprite()->runAction(m_pShootAction);

		m_shooted = true;
	}
	/////////////////////////
	// Schießen - Geschoss //
	/////////////////////////
	if (m_shooted)
	{
		if (m_counterToShoot == 15)
		{
			Bullet* nut = Bullet::createNut(this, this->getParent(), this->getPosition(), this->getSprite()->getScaleX(), 35.0f);
			this->getParent()->addChild(nut->getSprite(), 1);
			this->nuts.push_back(nut);
			m_shooted = false;
			m_counterToShoot = 0;
		}
		else
		{
			m_counterToShoot++;
		}
	}
	///////////////////////
	// Stehen - Bewegung //
	///////////////////////
	if (!m_pShoot->wasPressed() && !m_pForward->isPressed() && !m_pBackward->isPressed() && !m_pJump->isPressed() && !this->getSprite()->getActionByTag(4) && !this->getSprite()->getActionByTag(7))
	{
		if (!this->getSprite()->getActionByTag(0) && this->getGrounded())
		{
			this->getSprite()->stopAllActions();
			m_pStandAction = RepeatForever::create(Animate::create(m_pStandFrames));
			m_pStandAction->setTag(0);
			this->getSprite()->runAction(m_pStandAction);
		}
	}
	/////////////////////////
	// Springen - Bewegung //
	/////////////////////////
	if (m_pJump->wasPressed() && this->getGrounded())
	{
		addVelocity(0.0f, 600.0f);
		setPositionY(getPositionY() + 0.01);
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
	///////////////////////
	// Landen - Bewegung //
	///////////////////////
	else if (m_pJump->wasReleased() && m_isFlying || this->getGrounded() && m_jump)
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
	/////////////////////////////
	// Doppelsprung - Bewegung //
	/////////////////////////////
	else if (m_pJump->wasPressed() && !(this->getGrounded()) && !m_doubleJump && m_jump)
	{
		addVelocity(0.0f, 400.0f);
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
	if (m_movement & EMovement::Left && !m_shooted)
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
	if (m_movement & EMovement::Right && !m_shooted)
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
	///////////////////////
	// Fallen - Bewegung //
	///////////////////////
	if (!this->getGrounded() && !m_jump)
	{
		if (!m_readyToFall)
		{
			this->getSprite()->stopAllActions();
			m_pFallStartAction = Repeat::create(Animate::create(m_pFallStartFrames), 1);
			m_pFallStartAction->setTag(8);
			this->getSprite()->runAction(m_pFallStartAction);
			m_readyToFall = true;
		}
	}

	m_direction.x *= m_speed;
	this->setPosition(this->getPosition() + m_direction);
}

void Player::CheckForCollisions()
{
	bool collided = false;
	setGrounded(false);
	list<Ground*>* physObj = getParent()->getPhysicsObjects();
	for (Ground* g : *physObj)
	{
		if (g->getGround() == true)
		{			
			bool hack = false;
			Collider* c = g->getColliderComponent();
			
			if (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getTopCollider()) && !g->getWall())
			{
				if (m_topCollisionGround != nullptr)
				{
					m_topCollisionGround == nullptr;
				}
				else
				{
					if (m_bottomColWhileTopCol == false)
					{
						m_topCollision = true;
						m_topCollisionGround = g;
					}
				}
				collided = true;
			}
			else
			{
				Collider* topc = nullptr;
				if (m_topCollisionGround != nullptr)
					topc = m_topCollisionGround->getColliderComponent();
				
				if (m_topCollision == false && m_topCollisionGround == nullptr)
				{
					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
					{
						collided = true;
						hack = true;
						// kollision (boden)
						setGrounded(true);
						setPositionY(getPositionY() + 0.01f);
						getPlayerColliderComponent()->update(0.0f);

					}
				}
				else if (m_topCollision && c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
				{
					collided = true;
					m_bottomColWhileTopCol = true;
				}
				if (m_bottomColWhileTopCol == true)
				{
					if (topc != nullptr)
					{
						if (!topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
						{
							m_bottomColWhileTopCol = false;
							m_topCollision = false;
							collided = true;
						}
					}
				}
				if (hack)
				{
						setPositionY(getPositionY() - 0.01f);
						getPlayerColliderComponent()->update(0.0f);
				}
				if (m_topCollision == false && m_topCollisionGround == nullptr)
				{
					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getLeftCollider()))
					{
						setPositionX(getPositionX() + 0.01f);
						getPlayerColliderComponent()->update(0.0f);
						collided = true;
					}
					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getRightCollider()))
					{
						//Collision right wand
						setPositionX(getPositionX() - 0.01f);
						getPlayerColliderComponent()->update(0.0f);
						collided = true;
					}
				}
				if (topc != nullptr)
				{
					if (topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getLeftCollider()) &&
						topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getRightCollider()))
					{
						m_topCollision = true;
						collided = true;
					}
				}
			}
		}
		if (!collided)
		{
			m_bottomColWhileTopCol = false;
			m_topCollision = false;
			m_topCollisionGround = nullptr;
		}
	}
}

void Player::hit()
{
	m_health = m_health - 1;

	if (m_health != 0)
	{
		this->getSprite()->stopAllActions();
		m_pHitAction = Repeat::create(Animate::create(m_pHitFrames), 1);
		m_pHitAction->setTag(5);
		this->getSprite()->runAction(m_pHitAction);
	}
}

int Player::getHealth()
{
	return m_health;
}

int Player::getNuts()
{
	return m_nuts;
}

void Player::setNuts(int nuts)
{
	m_nuts = nuts;
}