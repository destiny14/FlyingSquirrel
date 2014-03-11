#include "Loewenzahn.h"
#include "Player.h"

USING_NS_CC;

Loewenzahn::Loewenzahn(PhysicsEngine* _pEn) : Shooter(_pEn)
{
}

Loewenzahn::~Loewenzahn()
{
}
//----------Create-----------//
Loewenzahn* Loewenzahn::create(PhysicsEngine* _pEn, MainLayer* layer)
{
	Loewenzahn* loewenzahn = new Loewenzahn(_pEn);


	Texture* tex = Texture::create("loewenzahn.png");
	loewenzahn->m_pPlayer = layer->getPlayer();

	if (tex)
	{
		loewenzahn->setTexture(tex);
		loewenzahn->setCollider(250.0f, 250.0f);
		loewenzahn->setParent(layer);

		loewenzahn->init();

		return loewenzahn;
	}

	return nullptr;
}
//----------Init mit animationen etc---------//
bool Loewenzahn::init()
{
	m_isAlive = true;

	//-----Animationen-----//

	m_pSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache();
	m_pSpriteFrame->addSpriteFramesWithFile("loewenzahn.plist");
	m_pSpriteBatch = SpriteBatchNode::create("loewenzahn.png");

	//-----Idle-----//		//--Tag_0--//

	for (int i = 0; i < 40; i++)
	{
		m_pSpriteString = String::createWithFormat("Idle%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pIdleFrames = Animation::createWithSpriteFrames(frames, 0.015f);
	m_pIdleFrames->retain();
	frames.clear();




	//-----Shoot-----//		//--Tag_1--//

	for (int i = 0; i < 51; i++)
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

	for (int i = 0; i < 10; i++)
	{
		m_pSpriteString = String::createWithFormat("Hit%i", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	for (int i = 0; i < 20; i++)
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
void Loewenzahn::setCollider(float width, float height)
{
	//Sprite* sprite = getSprite();
	//Rect boundingBox = sprite->getBoundingBox();

	/*Collider* collider = Collider::create(width, height);
	this->addComponent(collider);*/
}
//----------Collider abfragen---------//
//PlayerCollider* Loewenzahn::getPlayerColliderComponent()
//{
//	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
//}
//----------GameLoop-----------//
void Loewenzahn::update(float dt)
{

	//this->getPlayerColliderComponent()->update(dt);
	//this->setAffectedByGravity(false);
	Moveable::update(dt);
	//this->CheckForCollisions();

	if (this->m_isAlive)
	{

		if (canAttack())
		{
			this->moodAttack(dt);
		}
		else
		{
			this->moodIdle(dt);
		}

	}
	else if (!(this->m_isAlive))
	{
		this->moodDie(dt);
	}
}
//----------Laufen mit animation----------//
void Loewenzahn::moodIdle(float dt)
{

	if (!this->getSprite()->getActionByTag(0))
	{
		this->setScale(1);
		this->getSprite()->stopAllActions();
		m_pIdleAction = RepeatForever::create(Animate::create(m_pIdleFrames));
		m_pIdleAction->setTag(0);
		this->getSprite()->runAction(m_pIdleAction);
	}


}
//----------Attack (TODO wenn attack + collider = hit player)----------//
void Loewenzahn::moodAttack(float dt)
{

	if (!this->getSprite()->getActionByTag(1))
	{
		this->getSprite()->stopAllActions();
		m_pShootAction = Repeat::create(Animate::create(m_pShootFrames), 1);
		m_pShootAction->setTag(1);
		this->getSprite()->runAction(m_pShootAction);
	}

}
//---------Sterben (TODO Loewenzahn Löschen)----------//
void Loewenzahn::moodDie(float dt)
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
bool Loewenzahn::canAttack()
{
	playerPos = m_pPlayer->getPosition();
	loewenzahnPos = this->getPosition();

	if (abs(attackRange) >= (ccpDistance(playerPos, loewenzahnPos)))
	{
		if (playerPos.x > loewenzahnPos.x)
		{
			this->getSprite()->setScaleX(-1.0f);
			return true;
		}
		if (playerPos.x < loewenzahnPos.x)
		{
			this->getSprite()->setScaleX(1.0f);
			return true;
		}
	}
	return false;
}
//----------Collision TODO all!----------//
void Loewenzahn::CheckForCollisions()
{

}

