#include "SlimeHeap.h"
#include "Levelsystem\Objects\Player.h"

USING_NS_CC;

SlimeHeap::SlimeHeap()
{
}

SlimeHeap::~SlimeHeap()
{
}
//----------Create-----------//
SlimeHeap* SlimeHeap::create(MainLayer* layer)
{
	SlimeHeap* slimeHeap = new SlimeHeap();


	Texture* tex = Texture::create("slimeHeap.png");
	slimeHeap->m_pPlayer = layer->getPlayer();

	if (tex)
	{
		slimeHeap->setTexture(tex);
		slimeHeap->setCollider(250.0f, 120.0f);
		slimeHeap->setParent(layer);

		slimeHeap->init();

		return slimeHeap;
	}

	return nullptr;
}
//----------Init mit animationen etc---------//
bool SlimeHeap::init()
{
	m_isAlive = true;

	//-----Animationen-----//

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("slimeHeap.plist");
	m_pSpriteBatch = SpriteBatchNode::create("slimeHeap.png");

	//-----Walk-----//		//--Tag_0--//

	for (int i = 0; i < 90; i++)
	{
		m_pSpriteString = String::createWithFormat("Walk%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pWalkFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pWalkFrames->retain();
	frames.clear();




	//-----Shoot-----//		//--Tag_1--//

	for (int i = 0; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Shoot%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pShootFrames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pShootAction = Animate::create(m_pShootFrames);

	m_pShootFrames->retain();
	frames.clear();


	//-----Death-----//			//--Tag_2--//

	for (int i = 0; i < 25; i++)
	{
		m_pSpriteString = String::createWithFormat("Hit%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	for (int i = 0; i < 58; i++)
	{
		m_pSpriteString = String::createWithFormat("Dead%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}


	m_pDeadFrames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pDeadAction = Animate::create(m_pDeadFrames);

	m_pDeadFrames->retain();
	frames.clear();


	return true;
}
//----------Collider setzen----------//
void SlimeHeap::setCollider(float width, float height)
{
	//Sprite* sprite = getSprite();
	//Rect boundingBox = sprite->getBoundingBox();

	Collider* collider = Collider::create(width, height);
	this->addComponent(collider);
}
//----------Collider abfragen---------//
//PlayerCollider* SlimeHeap::getPlayerColliderComponent()
//{
//	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
//}
//----------GameLoop-----------//
void SlimeHeap::update(float dt)
{

	//this->getPlayerColliderComponent()->update(dt);
	//this->setAffectedByGravity(false);
	Moveable::update(dt, false);
	//this->CheckForCollisions();

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
	else if (!(this->m_isAlive))
	{
		this->moodDie(dt);
	}
}
//----------Laufen mit animation----------//
void SlimeHeap::moodWalk(float dt)
{

	if (!this->getSprite()->getActionByTag(0))
	{
		this->getSprite()->stopAllActions();
		m_pWalkAction = RepeatForever::create(Animate::create(m_pWalkFrames));
		m_pWalkAction->setTag(0);
		this->getSprite()->runAction(m_pWalkAction);
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
	if (m_timer <= -3)
	{
		m_moveDirection.x = 0.0f;
		m_timer = 3;
		//m_isAlive = false;
	}

	this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);

}
//----------Attack (TODO wenn attack + collider = hit player)----------//
void SlimeHeap::moodAttack(float dt)
{

	if (!this->getSprite()->getActionByTag(1))
	{
		this->getSprite()->stopAllActions();
		m_pShootAction = Repeat::create(Animate::create(m_pShootFrames), 1);
		m_pShootAction->setTag(1);
		this->getSprite()->runAction(m_pShootAction);
	}

}
//---------Sterben (TODO SlimeHeap Löschen)----------//
void SlimeHeap::moodDie(float dt)
{
	if (!this->getSprite()->getActionByTag(2))
	{
		this->getSprite()->stopAllActions();
		m_pDeadAction = Repeat::create(Animate::create(m_pDeadFrames), 1);
		m_pDeadAction->setTag(2);
		this->getSprite()->runAction(m_pDeadAction);
	}

}
//----------Kann Enemy angreifen? ----------//
bool SlimeHeap::canAttack()
{
	playerPosX = m_pPlayer->getPositionX();
	slimePosX = this->getPositionX();

	if (abs(attackRange) >= abs(playerPosX - slimePosX))
	{
		if (playerPosX > slimePosX)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPosX < slimePosX)
		{
			this->getSprite()->setScaleX(1.0f);
			return true;
		}
	}
	return false;
}
//----------Collision TODO all!----------//
//void SlimeHeap::CheckForCollisions()
//{
//
//}

