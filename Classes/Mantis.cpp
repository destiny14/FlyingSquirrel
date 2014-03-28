#include "Mantis.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Mantis::Mantis(PhysicsEngine* _pEn) : Shooter(_pEn)
{
}

Mantis::~Mantis()
{
}
//----------Create-----------//
Mantis* Mantis::create(PhysicsEngine* _pEn, MainLayer* layer)
{
	Mantis* mantis = new Mantis(_pEn);


	Texture* tex = Texture::create("mantis1.png");
	mantis->m_layer = layer;

	if (tex)
	{
		mantis->setTexture(tex);
		mantis->setSize(890.0f, 580.0f);
		mantis->setParentLayer(layer);
		mantis->setTag(TAG_MANTIS);
		mantis->init();

		return mantis;
	}

	return nullptr;
}
//----------Init mit animationen etc---------//
bool Mantis::init()
{
	m_isAlive = true;

	//-----Animationen-----//

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("mantis2.plist");
	m_pSpriteBatch = SpriteBatchNode::create("mantis2.png");

	//-----Idle-----//		//--Tag_0--//

	for (int i = 0; i < 35; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Idle(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pIdleFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pIdleFrames->retain();
	frames.clear();


	//-----Run-----//		//--Tag_1--//

	for (int i = 0; i < 35; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Run(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pRunFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pRunAction = Animate::create(m_pRunFrames);

	m_pRunFrames->retain();
	frames.clear();

	//-----Range Attack-----//			//--Tag_3--//

	for (int i = 0; i < 60; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_RangeAttack(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pRangeAttackFrames = Animation::createWithSpriteFrames(frames, 0.03f);
	m_pRangeAttackAction = Animate::create(m_pRangeAttackFrames);
	m_pRangeAttackFrames->retain();
	frames.clear();


	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("mantis1.plist");
	m_pSpriteBatch = SpriteBatchNode::create("mantis1.png");

	//-----Attack-----//			//--Tag_2--//

	for (int i = 0; i < 30; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Attack(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pAttackFrames = Animation::createWithSpriteFrames(frames, 0.025f);
	m_pAttackAction = Animate::create(m_pAttackFrames);
	m_pAttackFrames->retain();
	frames.clear();



	

	//-----Death-----//			//--Tag_4--//
	for (int i = 0; i < 10; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}
	for (int i = 0; i < 40; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Dead(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pDeathAction = Animate::create(m_pDeathFrames);
	m_pDeathFrames->retain();
	frames.clear();


	//-----Hit-----//			//--Tag_5--//

	for (int i = 0; i < 10; i++)
	{
		m_pSpriteString = String::createWithFormat("Mantis_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pHitFrames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pHitAction = Animate::create(m_pHitFrames);
	m_pHitFrames->retain();
	frames.clear();

	return true;
}

//----------GameLoop-----------//
void Mantis::update(float dt)
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
	playerPos = m_pPlayer->getPosition();
	mantisPos = this->getPosition();
	//log("YDistance: %f", ((m_pPlayer->getPositionY()) - (this->getPositionY())));

	if (m_health <= 0)
	{
		m_isAlive = false;
	}

	if (this->m_isAlive)
	{
		attackTimer -= dt;

		if (attackTimer <= 0.0f)
		{
			this->rangeAttack(dt);
		}
		else if (canAttack())
		{
			this->moodAttack(dt);
		}
		else if (!canAttack())
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

bool Mantis::onCollision(PhysicsObject* _other, int _myColliderTag)
{
	Moveable::onCollision(_other, _myColliderTag);
	if (_other->getTag() == TAG_BULLET)
	{
		Bullet* b = dynamic_cast<Bullet*>(_other);
		b->destroy();
		applyDamage();
		return true;
	}
	return false;
}

void Mantis::applyDamage()
{
	if (m_first)
	{
		m_health -= 1;
		m_first = !m_first;
	}

}
//----------Laufen mit animation----------//
void Mantis::moodWalk(float dt)
{
	if (abs(attackRange_Range) >= ccpDistance(playerPos, mantisPos))
	{
		auto sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
		if (!sound->isBackgroundMusicPlaying())
		{
			sound->playBackgroundMusic("sounds/music/b02.wav", true);
		}
		if (!this->getSprite()->getActionByTag(1))
		{
			this->getSprite()->stopAllActions();
			m_pRunAction = RepeatForever::create(Animate::create(m_pRunFrames));
			m_pRunAction->setTag(1);
			this->getSprite()->runAction(m_pRunAction);
		}

		if (playerPos.x < mantisPos.x)
		{

			m_moveDirection.x = -1.5f;
			this->getSprite()->setScaleX(1.0f);

		}
		else if (playerPos.x > mantisPos.x)
		{
			m_moveDirection.x = 1.5f;
			this->getSprite()->setScaleX(-1.0f);
		}


		this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);
	}
}
//----------Attack (TODO wenn attack + collider = hit player)----------//
void Mantis::moodAttack(float dt)
{

	/*if (!this->getSprite()->getActionByTag(2) && attackTimer)
	{
		attackTimer = 5.0f;
		this->getSprite()->stopAllActions();
		m_pAttackAction = Repeat::create(Animate::create(m_pAttackFrames), 1);
		m_pAttackAction->setTag(2);
		this->getSprite()->runAction(m_pAttackAction);
		if (m_pPlayer->getPlayerColliderComponent()->getLeftCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			|| m_pPlayer->getPlayerColliderComponent()->getRightCollider().intersectsRect(this->getColliderComponent()->getCollisionRectangle())
			)
		{
			m_pPlayer->hit();
		}
	}*/

}
//---------Sterben (TODO Mantis Löschen)----------//
void Mantis::moodDie(float dt)
{
	if (!this->getSprite()->getActionByTag(4))
	{
		this->getSprite()->stopAllActions();
		m_pDeathAction = Repeat::create(Animate::create(m_pDeathFrames), 1);
		m_pDeathAction->setTag(4);
		this->getSprite()->runAction(m_pDeathAction);
		m_isDead = true;
	}

}

void Mantis::rangeAttack(float dt)
{
	if (attackTimer <= -1.63f)
	{ 
		this->removeAllComponents();
		this->setSize(890.0f, 580.0f);
		this->setPosition(getTexture()->getPositionX(), getTexture()->getPositionY() - 5);
		attackTimer = 5.0f;
	}
	if (!this->getSprite()->getActionByTag(3))
	{
		this->removeAllComponents();
		this->setSize(890.0f, 780.0f);
		this->setPosition(getTexture()->getPositionX(), getTexture()->getPositionY() + 250);
		this->getSprite()->stopAllActions();
		m_pRangeAttackAction = Repeat::create(Animate::create(m_pRangeAttackFrames), 1);
		m_pRangeAttackAction->setTag(3);
		this->getSprite()->runAction(m_pRangeAttackAction);
	}
}
//----------Kann Enemy angreifen? ----------//
bool Mantis::canAttack()
{




	if (abs(attackRange_Meele) >= ccpDistance(playerPos, mantisPos))
	{
		if (playerPos.x > mantisPos.x)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPos.x < mantisPos.x)
		{
			this->getSprite()->setScaleX(1.0f);
			return true;
		}
	}
	return false;
}
//----------Collision TODO all!----------//
void Mantis::CheckForCollisions()
{

}

