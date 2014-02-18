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
	//m_visibleSize = Director::getInstance()->getVisibleSize();
	//m_origin = Director::getInstance()->getVisibleOrigin();

	m_sawyerRunFrame = 0;
	m_movement = None;
	m_direction.x = 0.0f;
	m_direction.y = 0.0f;
	m_speed = 100.0f;
	m_doubleJump = false;
	m_readyToFly = false;

	/*
	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();

	m_pSpriteFrame->addSpriteFramesWithFile("sawyer.plist");
	m_pSpriteBatch = SpriteBatchNode::create("sawyer.png");
	this->getParent()->addChild(m_pSpriteBatch, 10);

	m_pStandFrames = m_pSpriteFrame->getSpriteFrameByName("sawyerstand.png");
	m_pRunFrames = m_pSpriteFrame->getSpriteFrameByName("sawyerrun.png");
	m_pJumpFrames = m_pSpriteFrame->getSpriteFrameByName("sawyerjump.png");
	m_pHitFrames = m_pSpriteFrame->getSpriteFrameByName("sawyerhit.png");
	*/
	//Animation* anim = Animation::createWithSpriteFrames(

	
	m_pStandFrames = Sprite::create("sawyerstand.png", Rect(0.0f, 0.0f, 163.0f, 243.0f));
	m_pStandFrames->retain();
	m_pRunFrames = Sprite::create("sawyerrun.png", Rect(0.0f, 0.0f, 264.0f, 270.0f));
	m_pRunFrames->retain();
	m_pJumpFrames = Sprite::create("sawyerjump.png", Rect(0.0f, 0.0f, 283.0f, 272.0f));
	m_pJumpFrames->retain();
	m_pHitFrames = Sprite::create("sawyerhit.png", Rect(0.0f, 0.0f, 214.0f, 256.0f));
	m_pHitFrames->retain();
	

	/*m_pStandTex->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));
	m_pRunTex->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));
	m_pJumpTex->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));
	m_pHitTex->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));*/

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

	////////////////////////////////////////////
	// Rückwärts Gehen - Animation + Bewegung //
	////////////////////////////////////////////
	if (m_movement & EMovement::Left)
	{
		m_direction.x = -1.0f;
		this->getSprite()->setScaleX(-1.0f);
	}
	///////////////////////////////////////////
	// Vorwärts Gehen - Animation + Bewegung //
	///////////////////////////////////////////
	if (m_movement & EMovement::Right)
	{
		m_direction.x += 1.0f;
		this->getSprite()->setScaleX(1.0f);
	}

	m_direction.x *= m_speed;

	/////////////////////////////////////
	// Springen - Animation + Bewegung //
	/////////////////////////////////////
	if (m_pJump->wasPressed() && this->getGrounded())
	{
		addVelocity(0.0f, 300.0f);
	}
	/////////////////////////////////////////
	// Doppelsprung - Animation + Bewegung //
	/////////////////////////////////////////
	else if (m_pJump->wasPressed() && !(this->getGrounded()) && !m_doubleJump)
	{
		m_readyToFly = false;
		addVelocity(0.0f, 200.0f);
		m_doubleJump = true;
	}
	////////////////////////////////////
	// Fliegen - Animation + Bewegung //
	////////////////////////////////////
	else if (m_pJump->wasReleased())
	{
		m_readyToFly = true;
	}
	else if (m_pJump->isPressed() && !(this->getGrounded()) && m_doubleJump && m_readyToFly)
	{
		addVelocity((400.0f * this->getSprite()->getScaleX()), 0.0f);
	}

	//static float timeForHit = 0.075f;
	static float timeForStand = 0.065f;
	static float timeForRun = 0.0275f;

	/*if (m_direction.x != 0.0f && this->getGrounded())
	{
		timeForStand -= dt;
	}
	if (timeForStand < 0 && m_direction.x != 0.0f)
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
	if (m_direction.x != 0.0f && this->getGrounded())
	{
		timeForRun -= dt;
	}
	if (timeForRun < 0 && m_direction.x != 0.0f)
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
	

	this->setPosition(this->getPosition() + m_direction * dt);

	/*
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
	/*/
	////////////////////////////////////////////
	// Rückwärts Gehen - Animation + Bewegung //
	////////////////////////////////////////////
	else if (m_pBackward->isPressed() && this->getGrounded())
	{
		static float timeForRun = 0.0275f;
		if (strcmp(m_pState, "runBackward") != 0)
		{
			this->getTexture()->setSprite(m_pRunTex);
			//this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 264.0f, 270.0f));
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
	/////////////////////////////////////
	// Springen - Animation + Bewegung //
	/////////////////////////////////////
	else if (m_pJump->isPressed() && this->getGrounded())
	{
		static float timeForJump = 0.03f;
		if (strcmp(m_pState, "jump") != 0)
		{
			this->getTexture()->setSprite(m_pJumpTex);
			//this->getSprite()->setTextureRect(Rect(0.0f, 0.0f, 283.0f, 272.0f));
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
	}*/

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
			Collider* c = g->getColliderComponent();
			if (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
			{
				// kollision (boden)
				setGrounded(true);
				m_doubleJump = false;
			}
		}
	}
}