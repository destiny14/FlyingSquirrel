#include "Snail.h"
#include "Levelsystem\Objects\Player.h"

USING_NS_CC;

Snail::Snail()
{
}

Snail::~Snail()
{
}

Snail* Snail::create( MainLayer* layer)
{
	Snail* snail = new Snail();


	Texture* tex = Texture::create("snail.png");

	if (tex)
	{
		snail->setTexture(tex);
		snail->setCollider(200.0f, 120.0f);
		snail->setParent(layer);

		snail->init();

		return snail;
	}

	return nullptr;	
}

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

	m_pCrouchCycleFrames = Animation::createWithSpriteFrames(frames, 0.0025f);
	m_pCrouchCycleFrames->retain();
	frames.clear();


	//-----Punsh_1-----//		//--Tag_1--//

	for (int i = 0; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_1(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pPunch_1Frames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pPunch1Action = Animate::create(m_pPunch_1Frames);

	m_pPunch_1Frames->retain();
	frames.clear();

	//-----Punch_2-----//		//--Tag_1--//

	for (int i = 0; i < 85; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Punch_2(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pPunch_2Frames = Animation::createWithSpriteFrames(frames, 0.002f);
	m_pPunch2Action = Animate::create(m_pPunch_2Frames);

	m_pPunch_2Frames->retain();
	frames.clear();

	//-----Death-----//			//--Tag_2--//

	for (int i = 0; i < 58; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Death(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pDeathFrames = Animation::createWithSpriteFrames(frames, 0.002f);

	m_pDeathFrames->retain();
	frames.clear();

	//-----Hit-----//		//--Tag_3--//

	for (int i = 0; i < 25; i++)
	{
		m_pSpriteString = String::createWithFormat("Snail_Hit(%i).png", i);
		m_pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pSpriteString->getCString());
		frames.pushBack(m_pFrame);
	}

	m_pHitFrames = Animation::createWithSpriteFrames(frames, 0.002f);

	m_pHitFrames->retain();
	frames.clear();


	return true;
}

void Snail::setCollider(float width, float height)
{
	//Sprite* sprite = getSprite();
	//Rect boundingBox = sprite->getBoundingBox();

	m_pcollider = Collider::create(width, height);
	this->addComponent(m_pcollider);
}

void Snail::update(float dt)
{

	Moveable::update(dt, false);

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

		if (m_pcollider != nullptr)
		{
			m_pcollider->update(dt);
		}
	}
	else if (!(this->m_isAlive))
	{
		this->moodDie(dt);
	}

}


//TODO
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
		debugAttack = true;
	}

	this->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);

}

//TODO
void Snail::moodAttack(float dt)
{
	this->removeAllComponents();
	this->setCollider(290.0f, 120.0f);

	//if (!this->getSprite()->getActionByTag(1))
	//{
	//	this->getSprite()->stopAllActions();
	//	m_pPunchAction = RepeatForever::create(Sequence::create(m_pPunch1Action, m_pPunch2Action, nullptr));
	//	//m_pPunchAction = RepeatForever::create(Sequence::create((Animate::create(m_pPunch_1Frames)), (Animate::create(m_pPunch_2Frames))));
	//	//m_pPunsh1Action = Repeat::create(Animate::create(m_pPunch_1Frames), 1);
	//	//m_pPunsh1Action = RepeatForever::create(Animate::create(m_pPunch_1Frames));
	//	m_pPunchAction->setTag(1);
	//	this->getSprite()->runAction(m_pPunchAction);
	//}

}

//TODO
void Snail::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool Snail::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	if (debugAttack)
	{
		return true;
	}
	return false;
}

