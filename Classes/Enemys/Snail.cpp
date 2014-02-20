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


	Texture* tex = Texture::create("snail.png");
	snail->m_pPlayer = layer->getPlayer();

	if (tex)
	{
		snail->setTexture(tex);
		snail->setCollider(250.0f, 120.0f);
		snail->setParent(layer);

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


	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pDeathAction = Animate::create(m_pDeathFrames);

	m_pDeathFrames->retain();
	frames.clear();


	return true;
}
//----------Collider setzen----------//
void Snail::setCollider(float width, float height)
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	PlayerCollider* collider = PlayerCollider::create(width, height);
	this->addComponent(collider);
}
//----------Collider abfragen---------//
PlayerCollider* Snail::getPlayerColliderComponent()
{
	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
}
//----------GameLoop-----------//
void Snail::update(float dt)
{

	this->getPlayerColliderComponent()->update(dt);
	this->setAffectedByGravity(false);
	Moveable::update(dt, true);
	this->CheckForCollisions();

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
	if (m_timer <= -3)
	{
		m_moveDirection.x = 0.0f;
		m_timer = 3;
		m_isAlive = false;
	}

	this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);

}
//----------Attack (TODO wenn attack + collider = hit player)----------//
void Snail::moodAttack(float dt)
{

	if (!this->getSprite()->getActionByTag(1))
	{
		this->getSprite()->stopAllActions();
		m_pPunch1Action = Repeat::create(Animate::create(m_pPunch_1Frames), 1);
		m_pPunch1Action->setTag(1);
		this->getSprite()->runAction(m_pPunch1Action);
	}

}
//---------Sterben (TODO Snail L�schen)----------//
void Snail::moodDie(float dt)
{
	if (!this->getSprite()->getActionByTag(2))
	{
		this->getSprite()->stopAllActions();
		m_pDeathAction = Repeat::create(Animate::create(m_pDeathFrames), 1);
		m_pDeathAction->setTag(2);
		this->getSprite()->runAction(m_pDeathAction);
	}

}
//----------Kann Enemy angreifen? ----------//
bool Snail::canAttack()
{
	playerPosX = m_pPlayer->getPositionX();
	snailPosX = this->getPositionX();

	if (abs(attackRange) >= abs(playerPosX - snailPosX))
	{
		if (playerPosX > snailPosX)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPosX < snailPosX)
		{
			this->getSprite()->setScaleX(1.0f);
			return true;
		}
	}
	return false;
}
//----------Collision TODO all!----------//
void Snail::CheckForCollisions()
{
	
}

