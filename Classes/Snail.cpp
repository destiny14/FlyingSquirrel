#include "Snail.h"
#include "Player.h"

USING_NS_CC;

Snail::Snail(PhysicsEngine* _pEn) : Shooter(_pEn)
{
	m_moveDirection.x = 1.0f;
	m_tmpTimer = 3.0f;
}

Snail::~Snail()
{
}
//----------Create-----------//
Snail* Snail::create(PhysicsEngine* _pEn, MainLayer* layer)
{
	Snail* snail = new Snail(_pEn);

	snail->m_layer = layer;
	Texture* tex = Texture::create("snail.png");

	if (tex)
	{
		snail->setTexture(tex);
		snail->setSize(124.0f, 73.0f);
		snail->setParentLayer(layer);
		snail->setTag(TAG_SNAIL);
		snail->init();
		return snail;
	}

	return nullptr;	
}
//----------Init mit animationen etc---------//
bool Snail::init()
{
	m_isAlive = true;

	//-----Animationen-----//

	m_pSpriteFrame = SpriteFrameCache::getInstance();
	m_pSpriteFrame->addSpriteFramesWithFile("snail.plist");
	m_pSpriteBatch = SpriteBatchNode::create("snail.png");

	//-----Crouch_Cycle-----//		//--Tag_0--//

	for (int i = 1; i < 90; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Crouchcycle(%i).png", i);
		m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pCrouchCycleFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pCrouchCycleFrames->retain();
	frames.clear();


	//-----Punsh_1-----//		//--Tag_1--//

	for (int i = 1; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_1(%i).png", i);
		m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}
	for (int i = 1; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_2(%i).png", i);
		m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pPunch_1Frames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pPunch1Action = Animate::create(m_pPunch_1Frames);

	m_pPunch_1Frames->retain();
	frames.clear();


	//-----Death-----//			//--Tag_2--//

	for (int i = 1; i < 25; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	for (int i = 1; i < 58; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Death(%i).png", i);
		m_pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}


	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.02f);
	m_pDeathAction = Animate::create(m_pDeathFrames);

	m_pDeathFrames->retain();
	frames.clear();

	scheduleUpdate();

	return true;
}

//----------GameLoop-----------//
void Snail::update(float dt)
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
	if (this->getAffectedByGrafity() == false)
	{
		this->setAffectedByGravity(true);
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

}

void Snail::killIt()
{
	m_isAlive = false;
}
//----------Laufen mit animation----------//
void Snail::moodWalk(float dt)
{
	m_timer -= dt;
	if (!this->getSprite()->getActionByTag(0))
	{
		this->getSprite()->stopAllActions();
		m_pCrouchAction = RepeatForever::create(Animate::create(m_pCrouchCycleFrames));
		m_pCrouchAction->setTag(0);
		this->getSprite()->runAction(m_pCrouchAction);
	}
	
	if (m_timer < 0)
	{
		m_moveDirection.x *= -1.0f;
		m_timer = m_tmpTimer;
		velocity.x = m_moveDirection.x * m_speed;
		this->getSprite()->setScaleX(-m_moveDirection.x);
	}

	//this->setPositionX(this->getPositionX() + m_moveDirection.x);

}

bool Snail::onCollision(PhysicsObject* _other, int _myColliderTag)
{
	if (_other->getTag() == TAG_BULLET)
	{
		Bullet* b = dynamic_cast<Bullet*>(_other);
		b->destroy();
		killIt();
	}

	if (_other->getTag() == TAG_PLAYER && _myColliderTag == up->getTag() && _other->getCollider()->getTag() == bot->getTag() && _other->velocity.y < 2.0f)
	{
		killIt();
	}
	else if (_other->getTag() == TAG_PLAYER && m_canAttack)
	{
		m_pPlayer->hit();
		m_canAttack = false;
	}

	return Moveable::onCollision(_other, _myColliderTag);
}

float Snail::getTimer()
{
	return m_timer;
}

void Snail::setTimer(float seconds)
{
	m_timer = seconds;
	m_tmpTimer = seconds;
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
	}
	if (!m_canAttack)
	{
		m_attackTimer -= dt;
		if (m_attackTimer <= 0)
		{
			m_canAttack = true;
			m_attackTimer = 1.0f;
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
		removeFromParentAndCleanup(true); // gegner entfernen
		
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

