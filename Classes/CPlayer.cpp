#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "MainLayer.h"
#include "Player.h"
#include "Collider.h"

Player* Player::create(PhysicsEngine* _pEn, char* filename, MainLayer* parent, InputManager* pManager)
{
	Player* player = new Player(_pEn);

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
		player->setSize(80.0f, 125.0f);
		player->setParent(parent);
		player->init();

		return player;
	}
	return nullptr;
}

Player::Player(PhysicsEngine* _pEn) : Shooter(_pEn) {}

Player::~Player() {}

bool Player::init()
{
	Shooter* shooter = Shooter::create(this->getPhysicsEngine(), this->getTexture()->getFilename(), this->getParentLayer());

	m_health = 3;
	m_nuts = 5;

	m_counterDeath = 0;
	m_counterToShoot = 0;
	m_counterToFall = 0;
	m_counterToRescueFly = 0;
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
	m_noNuts = false;
	m_flySound = false;
	m_topCollision = false;
	m_bottomColWhileTopCol = false;
	m_topCollisionGround = nullptr;

	cs_flight = false;
	cs_run = false;

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
	m_pFallFrames = Animation::createWithSpriteFrames(frames, 0.03f);
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
	/////////////////////////////////////
	// Dont know direction - Animation // // 11
	/////////////////////////////////////
	for (int i = 0; i < 35; i++)
	{
		filename = String::createWithFormat("skeleton-Idle2%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pDontKnowDirectionFrames = Animation::createWithSpriteFrames(frames, 0.0325f);
	m_pDontKnowDirectionFrames->retain();
	frames.clear();
	////////////////////////////
	// Jump Shoot - Animation // // 12
	////////////////////////////
	for (int i = 0; i < 51; i++)
	{
		filename = String::createWithFormat("skeleton-Jump_shot%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pJumpShootFrames = Animation::createWithSpriteFrames(frames, 0.025f);
	m_pJumpShootFrames->retain();
	frames.clear();
	/////////////////////////////
	// Double Jump - Animation // // 13
	/////////////////////////////
	for (int i = 0; i < 58; i++)
	{
		filename = String::createWithFormat("skeleton-Double_Jump%i.png", i);
		frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		frames.pushBack(frame);
	}
	m_pDoubleJumpFrames = Animation::createWithSpriteFrames(frames, 0.008f);
	m_pDoubleJumpFrames->retain();
	frames.clear();

	this->getSprite()->runAction(m_pStandAction);

	return true;
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

	Shooter::update(dt);
	
	m_direction.x = 0.0f;
	velocity.x = 0.0f;

	////////////////////////////////
	// Tod - Bewegung - SPIELENDE //
	////////////////////////////////
	if (m_health > 0)
	{
		
	}
	else if (m_health <= 0 && !m_isDead)
	{
		velocity.x += -750.0f * this->getScaleX();
		velocity.y += -300.0f;
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
		velocity.y += -500.0f;
		return;
	}
	/////////////////////////
	// Schießen - Bewegung //
	/////////////////////////
	if (m_pShoot->wasPressed() && m_nuts > 0 && this->isGrounded())
	{
		this->getSprite()->stopAllActions();
		m_pShootAction = Repeat::create(Animate::create(m_pShootFrames), 1);
		m_pShootAction->setTag(7);
		this->getSprite()->runAction(m_pShootAction);

		m_countToShoot = 15;
		m_noNuts = false;
		m_shooted = true;
	}
	else if (m_pShoot->wasPressed() && m_nuts > 0 && !this->isGrounded() && m_jump)
	{
		this->getSprite()->stopAllActions();
		m_pJumpShootAction = Repeat::create(Animate::create(m_pJumpShootFrames), 1);
		m_pJumpShootAction->setTag(12);
		this->getSprite()->runAction(m_pJumpShootAction);

		m_countToShoot = 40;
		m_noNuts = false;
		m_shooted = true;
	}
	else if (m_pShoot->wasPressed() && !this->getSprite()->getActionByTag(11) && this->isGrounded() && !m_shooted)
	{
		this->getSprite()->stopAllActions();
		m_pDontKnowDirectionAction = Repeat::create(Animate::create(m_pDontKnowDirectionFrames), 1);
		m_pDontKnowDirectionAction->setTag(11);
		this->getSprite()->runAction(m_pDontKnowDirectionAction);

		m_noNuts = true;
	}
	/////////////////////////
	// Schießen - Geschoss //
	/////////////////////////
	if (m_shooted)
	{
		if (m_counterToShoot == m_countToShoot)
		{
			auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
			sound->playEffect("sounds/sawyer/Schuss.wav", false, 1.0f, 0.0f, 1.0f);
			Bullet* nut = Bullet::createNut(this, this->getParentLayer(), this->getPosition(), this->getSprite()->getScaleX(), 35.0f);
			this->getParent()->addChild(nut->getSprite(), 1);
			this->nuts.push_back(nut);
			m_shooted = false;
			m_nuts = m_nuts - 1;
			m_counterToShoot = 0;
			m_countToShoot = 0;
		}
		else
		{
			m_counterToShoot++;
		}
	}
	/////////////////////////
	// Verwirrt - Bewegung //
	/////////////////////////
	if (m_pForward->isPressed() && m_pBackward->isPressed())
	{
		if (!this->getSprite()->getActionByTag(11) && this->isGrounded())
		{
		this->getSprite()->stopAllActions();
		m_pDontKnowDirectionAction = Repeat::create(Animate::create(m_pDontKnowDirectionFrames), 1);
		m_pDontKnowDirectionAction->setTag(11);
		this->getSprite()->runAction(m_pDontKnowDirectionAction);
		}
	}
	///////////////////////
	// Stehen - Bewegung //
	///////////////////////
	if (!m_pShoot->wasPressed() && !m_pForward->isPressed() && !m_pBackward->isPressed() && !m_pJump->isPressed() && !this->getSprite()->getActionByTag(4) && !this->getSprite()->getActionByTag(7) && !this->getSprite()->getActionByTag(11))
	{
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		sound->stopAllEffects();
		if (!this->getSprite()->getActionByTag(0) && this->isGrounded())
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
	if (m_pJump->wasPressed() && this->isGrounded())
	{
		//setGrounded(false);
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		sound->playEffect("sounds/sawyer/Sprung.wav", false, 1.0f, 0.0f, 1.0f);
		velocity.y = 100.0f;
		//setPositionY(getPositionY() + 0.01);
		//this->setGrounded(false);
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
	else if (m_pJump->wasReleased() && m_isFlying || this->isGrounded() && m_jump || this->isGrounded() && m_readyToFall)
	{
		this->getSprite()->stopAllActions();
		m_pLandingAction = Repeat::create(Animate::create(m_pLandingFrames), 1);
		m_pLandingAction->setTag(4);
		this->getSprite()->runAction(m_pLandingAction);
		m_jump = false;
		m_doubleJump = false;
		m_readyToFly = false;
		m_readyToFall = false;
		m_rescueFly = false;
		m_isFlying = false;
		m_flySound = false;
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		sound->stopAllEffects();
	}
	/////////////////////////////
	// Doppelsprung - Bewegung //
	/////////////////////////////
	else if (m_pJump->wasPressed() && !(this->isGrounded()) && !m_doubleJump && m_jump)
	{
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		sound->playEffect("sounds/sawyer/Dsprung.wav", false, 1.0f, 0.0f, 1.0f);
		velocity.y += 40.0f;
		m_doubleJump = true;
		m_readyToFly = false;
		if (!this->getSprite()->getActionByTag(13))
		{
			this->getSprite()->stopAllActions();
			m_pDoubleJumpAction = Repeat::create(Animate::create(m_pDoubleJumpFrames), 1);
			m_pDoubleJumpAction->setTag(13);
			this->getSprite()->runAction(m_pDoubleJumpAction);
		}
	}
	////////////////////////
	// Fliegen - Bewegung //
	////////////////////////
	else if (m_pJump->wasReleased() && !m_isFlying && m_doubleJump)
	{
		m_readyToFly = true;
		m_flySound = false;
	}
	else if (m_pJump->isPressed() && m_doubleJump && m_readyToFly || cs_flight)
	{
		if (!m_flySound)
		{
			auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
			sound->playEffect("sounds/sawyer/Fstart.wav", false, 1.0f, 0.0f, 1.0f);
			if (!sound->isBackgroundMusicPlaying() && !m_flySound)
			{
				auto sound2 = CocosDenshion::SimpleAudioEngine::sharedEngine();
				sound2->playEffect("sounds/sawyer/Fliegen.wav", true, 1.0f, 0.0f, 1.0f);
				m_flySound = true;
			}
		}
		if (!this->getSprite()->getActionByTag(3))
		{
			this->getSprite()->stopAllActions();
			m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			this->getSprite()->runAction(m_pFlightAction);
		}

		m_isFlying = true;
		velocity.x = 100.0f * this->getSprite()->getScaleX();
		velocity.y = 20.0f;
	}
	////////////////////////////////
	// Rückwärts Gehen - Bewegung //
	////////////////////////////////
	/*if (m_pForward->isPressed() || m_pBackward->isPressed())
	{
		auto sound1 = CocosDenshion::SimpleAudioEngine::sharedEngine();
		sound1->playEffect("sounds/sawyer/step1.wav", true, 1.0f, 0.0f, 1.0f);
		auto sound2 = CocosDenshion::SimpleAudioEngine::sharedEngine();
		auto sound3 = CocosDenshion::SimpleAudioEngine::sharedEngine();
		if (!sound2->isBackgroundMusicPlaying())
		{
			sound1->playEffect("sounds/sawyer/step1.wav", false, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			sound2->playEffect("sounds/sawyer/step2.wav", false, 1.0f, 0.0f, 1.0f);
		}
	}*/
	if (m_movement & EMovement::Left && !m_shooted && !m_pForward->isPressed())
	{
		velocity.x = -100.0f;

		if (!this->getSprite()->getActionByTag(1) && this->isGrounded())
		{
			this->getSprite()->stopAllActions();
			m_pRunAction = RepeatForever::create(Animate::create(m_pRunFrames));
			m_pRunAction->setTag(1);
			this->getSprite()->runAction(m_pRunAction);
		}
		this->getSprite()->setScaleX(-1.0f);
	}
	////////////////////////
	// Cutscene - Trigger //
	////////////////////////
	if (cs_flight && this->isGrounded())
	{
		cs_flight = false;
		cs_run = true;
	}
	///////////////////////////////
	// Vorwärts Gehen - Bewegung //
	///////////////////////////////
	if (m_movement & EMovement::Right && !m_shooted && !m_pBackward->isPressed() || cs_run)
	{
		velocity.x = 100.0f;

		if (!this->getSprite()->getActionByTag(1) && this->isGrounded())
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

	auto flySound = CocosDenshion::SimpleAudioEngine::sharedEngine();

	if (!this->isGrounded() && !m_jump && !m_readyToFall)
	{
		if (!this->getSprite()->getActionByTag(8))
		{
			this->getSprite()->stopAllActions();
			m_pFallStartAction = Repeat::create(Animate::create(m_pFallStartFrames), 1);
			m_pFallStartAction->setTag(8);
			this->getSprite()->runAction(m_pFallStartAction);
		}
		if (m_counterToFall == 4)
		{
			m_readyToFall = true;
			m_counterToFall = 0;
		}
		else
		{
			m_counterToFall++;
		}
	}
	else if (!this->getSprite()->getActionByTag(9) && !this->isGrounded() && !m_jump && m_readyToFall && !m_pJump->isPressed())
	{
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		if (!sound->isBackgroundMusicPlaying())
		{
			sound->playEffect("sounds/sawyer/Fliegen.wav", true, 1.0f, 0.0f, 1.0f);
		}
		m_readyToFall = true;
		this->getSprite()->stopAllActions();
		m_pFallAction = RepeatForever::create(Animate::create(m_pFallFrames));
		m_pFallAction->setTag(9);
		this->getSprite()->runAction(m_pFallAction);
	}
	else if (m_pJump->isPressed() && !this->isGrounded() && m_readyToFall && !m_rescueFly)
	{
		if (!this->getSprite()->getActionByTag(10))
		{
			if (!flySound->isBackgroundMusicPlaying())
			{
				flySound->playEffect("sounds/sawyer/Fstart.wav", false, 1.0f, 0.0f, 1.0f);
			}
			this->getSprite()->stopAllActions();
			m_pFallToFlyAction = Repeat::create(Animate::create(m_pFallToFlyFrames), 1);
			m_pFallToFlyAction->setTag(10);
			this->getSprite()->runAction(m_pFallToFlyAction);
		}
		if (m_counterToRescueFly == 6)
		{
			m_rescueFly = true;
			m_counterToRescueFly = 0;
		}
		else
		{
			m_counterToRescueFly++;
		}
	}
	else if (m_pJump->isPressed() && !this->isGrounded() && m_rescueFly)
	{
		if (!this->getSprite()->getActionByTag(3))
		{
			auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
			if (!sound->isBackgroundMusicPlaying() && !flySound->isBackgroundMusicPlaying())
			{
				flySound->playEffect("sounds/sawyer/Fliegen.wav", true, 1.0f, 0.0f, 1.0f);
			}
			this->getSprite()->stopAllActions();
			m_pFlightAction = RepeatForever::create(Animate::create(m_pFlightFrames));
			m_pFlightAction->setTag(3);
			this->getSprite()->runAction(m_pFlightAction);
		}

		m_isFlying = true;
		velocity.x = 200.0f * this->getSprite()->getScaleX();
		velocity.y = 20.0f;
	}

	//velocity.x *= m_speed;
	//this->setPosition(this->getPosition() + m_direction);
}
//
//void Player::CheckForCollisions()
//{
//	bool collided = false;
//	setGrounded(false);
//	list<Ground*>* physObj = getParent()->getPhysicsObjects();
//	for (Ground* g : *physObj)
//	{
//		if (g->getGround() == true)
//		{			
//			bool hack = false;
//			Collider* c = g->getColliderComponent();
//			
//			if (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getTopCollider()) && !g->getWall())
//			{
//				if (m_topCollisionGround != nullptr)
//				{
//					m_topCollisionGround == nullptr;
//				}
//				else
//				{
//					if (m_bottomColWhileTopCol == false)
//					{
//						m_topCollision = true;
//						m_topCollisionGround = g;
//					}
//				}
//				collided = true;
//			}
//			else
//			{
//				Collider* topc = nullptr;
//				if (m_topCollisionGround != nullptr)
//					topc = m_topCollisionGround->getColliderComponent();
//				
//				if (m_topCollision == false && m_topCollisionGround == nullptr)
//				{
//					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
//					{
//						collided = true;
//						hack = true;
//						// kollision (boden)
//						setGrounded(true);
//						setPositionY(getPositionY() + 0.01f);
//						getPlayerColliderComponent()->update(0.0f);
//
//					}
//				}
//				else if (m_topCollision && c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
//				{
//					collided = true;
//					m_bottomColWhileTopCol = true;
//				}
//				if (m_bottomColWhileTopCol == true)
//				{
//					if (topc != nullptr)
//					{
//						if (!topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
//						{
//							m_bottomColWhileTopCol = false;
//							m_topCollision = false;
//							collided = true;
//						}
//					}
//				}
//				if (hack)
//				{
//						setPositionY(getPositionY() - 0.01f);
//						getPlayerColliderComponent()->update(0.0f);
//				}
//				if (g->getWall() == false && m_topCollision == false && m_topCollisionGround == nullptr)
//				{
//					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getLeftCollider()))
//					{
//						setPositionX(getPositionX() + 0.01f);
//						getPlayerColliderComponent()->update(0.0f);
//						collided = true;
//					}
//					while (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getRightCollider()))
//					{
//						//Collision right wand
//						setPositionX(getPositionX() - 0.01f);
//						getPlayerColliderComponent()->update(0.0f);
//						collided = true;
//					}
//				}
//				if (topc != nullptr)
//				{
//					if (topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getLeftCollider()) &&
//						topc->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getRightCollider()))
//					{
//						m_topCollision = true;
//						collided = true;
//					}
//				}
//			}
//		}
//		if (!collided)
//		{
//			m_bottomColWhileTopCol = false;
//			m_topCollision = false;
//			m_topCollisionGround = nullptr;
//		}
//	}
//}

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