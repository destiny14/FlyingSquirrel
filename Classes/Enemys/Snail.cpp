#include "Snail.h"
#include "Levelsystem\Objects\Player.h"

USING_NS_CC;

Snail::Snail()
{
}

Snail::~Snail()
{
}
//----------Create-----------//
Snail* Snail::create( MainLayer* layer)
{
	Snail* snail = new Snail();

	m_layer = layer;
	Texture* tex = Texture::create("snail.png");

	if (tex)
	{
		snail->setTexture(tex);
		snail->setCollider(350.0f, 120.0f);
		snail->setParent(layer);

		snail->init();
		snail->setTag(TAG_SNAIL);
		return snail;
	}

	return nullptr;	
}
//----------Init mit animationen etc---------//
bool Snail::init()
{
	m_isAlive = true;

	//-----Animationen-----//

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("snail.plist");
	m_pSpriteBatch = SpriteBatchNode::create("snail.png");

	//-----Crouch_Cycle-----//		//--Tag_0--//

	for (int i = 0; i < 90; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Crouchcycle(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pCrouchCycleFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pCrouchCycleFrames->retain();
	frames.clear();


	//-----Punsh_1-----//		//--Tag_1--//

	for (int i = 0; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_1(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}
	for (int i = 0; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_2(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pPunch_1Frames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pPunch1Action = Animate::create(m_pPunch_1Frames);

	m_pPunch_1Frames->retain();
	frames.clear();


	//-----Death-----//			//--Tag_2--//

	for (int i = 0; i < 25; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	for (int i = 0; i < 58; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Death(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}


	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pDeathAction = Animate::create(m_pDeathFrames);

	m_pDeathFrames->retain();
	frames.clear();


	return true;
}
//----------Collider setzen----------//
void Snail::setCollider(float width, float height)
{
	//Sprite* sprite = getSprite();
	//Rect boundingBox = sprite->getBoundingBox();

	Collider* collider = Collider::create(width, height);
	this->addComponent(collider);
}
//----------Collider abfragen---------//
//PlayerCollider* Snail::getPlayerColliderComponent()
//{
//	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
//}
//----------GameLoop-----------//
void Snail::update(float dt)
{
	if (m_pPlayer == nullptr)
	{
		this->m_pPlayer = m_layer->getPlayer();
	}
	//log("Ydistance: %f", ((m_pPlayer->getPositionY())-(this->getPositionY())));
	//this->getPlayerColliderComponent()->update(dt);
	//this->setAffectedByGravity(false);
	Moveable::update(dt, false);
	//this->CheckForCollisions();

	if (m_pPlayer->getPlayerColliderComponent()->getBottomCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
		&& ((m_pPlayer->getPositionY()) - (this->getPositionY())) >=170)
	{
		m_isAlive = false;
	}

	if (this->m_isAlive)
	{

		if (canAttack())
		{
			this->moodAttack(dt);
		}
		else
		{
			this->moodWalk(dt);

		}

	}
	else if (!(this->m_isAlive) && !m_isDead)
	{
		this->moodDie(dt);
	}
	else
	{
		//DO NOTHING
	}
}

void Snail::killIt()
{
	m_isAlive = false;
}
//----------Laufen mit animation----------//
void Snail::moodWalk(float dt)
{

	if (!this->getSprite()->getActionByTag(0))
	{
		this->getSprite()->stopAllActions();
		m_pCrouchAction = RepeatForever::create(Animate::create(m_pCrouchCycleFrames));
		m_pCrouchAction->setTag(0);
		this->getSprite()->runAction(m_pCrouchAction);
	}
	
	if (m_timer >= 0)
	{

		m_moveDirection.x = -1.0f;
		m_timer -= dt;
		this->getSprite()->setScaleX(1.0f);

	}
	else if (m_timer < 0)
	{
		m_moveDirection.x = 1.0f;
		m_timer -= dt;
		this->getSprite()->setScaleX(-1.0f);
	}
	if (m_timer <= -m_timer)
	{
		m_moveDirection.x = 0.0f;
		m_timer = m_timer;
		//m_isAlive = false;
	}

	this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);

}

float Snail::getTimer()
{
	return m_timer;
}

void Snail::setTimer(float seconds)
{
	m_timer = seconds;
}

//----------Attack (TODO wenn attack + collider = hit player)----------//
void Snail::moodAttack(float dt)
{

	if (!this->getSprite()->getActionByTag(1))
	{
		this->getSprite()->stopAllActions();
		m_pPunch1Action = RepeatForever::create(Animate::create(m_pPunch_1Frames));
		m_pPunch1Action->setTag(1);
		this->getSprite()->runAction(m_pPunch1Action);

		if (m_pPlayer->getPlayerColliderComponent()->getLeftCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			|| m_pPlayer->getPlayerColliderComponent()->getRightCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			)
		{
			m_pPlayer->hit();
		}
	}
}
//---------Sterben (TODO Snail Löschen)----------//
void Snail::moodDie(float dt)
{
	if (!this->getSprite()->getActionByTag(2))
	{
		this->getSprite()->stopAllActions();
		m_pDeathAction = Repeat::create(Animate::create(m_pDeathFrames), 1);
		m_pDeathAction->setTag(2);
		this->getSprite()->runAction(m_pDeathAction);
		m_isDead = true;
	}

}
//----------Kann Enemy angreifen? ----------//
bool Snail::canAttack()
{
	playerPos = m_pPlayer->getPosition();
	snailPos = this->getPosition();

	if (abs(attackRange) >= abs(ccpDistance(playerPos, snailPos)))
	{
		if (playerPos.x > snailPos.x)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPos.x < snailPos.x)
		{
			this->getSprite()->setScaleX(1.0f);
			return true;
		}
	}
	return false;
}
////----------Collision TODO all!----------//
//void Snail::CheckForCollisions()
//{
//	
//}

