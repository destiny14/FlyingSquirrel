#include "SlimeHeap.h"
#include "Player.h"

USING_NS_CC;

SlimeHeap::SlimeHeap(PhysicsEngine* _pEn) : Shooter(_pEn)
{
}

SlimeHeap::~SlimeHeap()
{
}

float SlimeHeap::getTimer()
{
	return m_timer;
}

void SlimeHeap::setTimer(float seconds)
{
	m_timer = seconds;
}
//----------Create-----------//
SlimeHeap* SlimeHeap::create(PhysicsEngine* _pEn, MainLayer* layer)
{
	SlimeHeap* slimeHeap = new SlimeHeap(_pEn);


	Texture* tex = Texture::create("slimeHeap.png");
	slimeHeap->m_layer = layer;

	if (tex)
	{
		slimeHeap->setTexture(tex);
		slimeHeap->setSize(250.0f, 125.0f);
		slimeHeap->setParentLayer(layer);
		slimeHeap->setTag(TAG_SLIMEHEAP);
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

	for (int i = 0; i < 81; i++)
	{
		m_pSpriteString = String::createWithFormat("SlimeHeap_Walk(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pWalkFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pWalkFrames->retain();
	frames.clear();




	//-----Shoot-----//		//--Tag_1--//

	for (int i = 0; i < 32; i++)
	{
		m_pSpriteString = String::createWithFormat("SlimeHeap_Shoot(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pShootFrames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pShootAction = Animate::create(m_pShootFrames);

	m_pShootFrames->retain();
	frames.clear();


	//-----Death-----//			//--Tag_2--//

	for (int i = 0; i < 24; i++)
	{
		m_pSpriteString = String::createWithFormat("SlimeHeap_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	for (int i = 0; i < 45; i++)
	{
		m_pSpriteString = String::createWithFormat("SlimeHeap_Dead(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}


	m_pDeadFrames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pDeadAction = Animate::create(m_pDeadFrames);

	m_pDeadFrames->retain();
	frames.clear();

	scheduleUpdate();

	return true;
}

//----------GameLoop-----------//
void SlimeHeap::update(float dt)
{
	if (m_pPlayer == nullptr)
	{
		this->m_pPlayer = m_layer->getPlayer();
		return;
	}

	//this->getPlayerColliderComponent()->update(dt);
	//this->setAffectedByGravity(false);
	Moveable::update(dt);
	//this->CheckForCollisions();

	//if (m_pPlayer->getPlayerColliderComponent()->getBottomCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
	//	&& ((m_pPlayer->getPositionY()) - (this->getPositionY())) >= 170)
	//{
	//	m_isAlive = false;
	//}

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

void SlimeHeap::killIt()
{
	m_isAlive = false;
}

bool SlimeHeap::onCollision(PhysicsObject* _other, int _myColliderTag)
{
	Moveable::onCollision(_other, _myColliderTag);
	if (_other->getTag() == TAG_BULLET)
	{
		Bullet* b = dynamic_cast<Bullet*>(_other);
		b->destroy();
		killIt();
		return true;
	}
	return false;
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
	if (m_timer <= -m_timer)
	{
		m_moveDirection.x = 0.0f;
		m_timer = m_timer;
		//m_isAlive = false;
	}

	this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);

}
//----------Attack (TODO wenn attack + collider = hit player)----------//
void SlimeHeap::moodAttack(float dt)
{

	/*if (!this->getSprite()->getActionByTag(1))
	{
		this->getSprite()->stopAllActions();
		m_pShootAction = RepeatForever::create(Animate::create(m_pShootFrames));
		m_pShootAction->setTag(1);
		this->getSprite()->runAction(m_pShootAction);

		if (m_pPlayer->getPlayerColliderComponent()->getLeftCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			|| m_pPlayer->getPlayerColliderComponent()->getRightCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			)
		{
			m_pPlayer->hit();
		}
	}*/

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
		m_isDead = true;


	}

}
//----------Kann Enemy angreifen? ----------//
bool SlimeHeap::canAttack()
{
	playerPos = m_pPlayer->getPosition();
	slimePos = this->getPosition();

	if (abs(attackRange) >= abs(ccpDistance(playerPos, slimePos)))
	{
		if (playerPos.x > slimePos.x)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPos.x < slimePos.x)
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

