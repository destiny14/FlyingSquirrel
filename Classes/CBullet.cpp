#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Bullet.h"
#include "Collider.h"
#include "Shooter.h"
#include "SimpleAudioEngine.h"

Bullet* Bullet::createNut(Shooter* shooter, MainLayer* parent, Point position, float direction, float force)
{
	Bullet* bullet = new Bullet(shooter->getPhysicsEngine());
	Texture* tex = Texture::create("nuss.png");
	/*bullet->m_pSnail = parent->getSnail();
	bullet->m_pSlimeHeap = parent->getSlimeHeap();
	bullet->m_pMantis = parent->getMantis();*/

	tex->retain();

	bullet->setTexture(tex);
	bullet->setParent(parent);
	bullet->setSize(50, 59);
	bullet->setPosition(position.x + (100.0f * direction), position.y + 25.0f);
	bullet->setAffectedByGravity(true);
	bullet->getSprite()->setScale(0.5f);
	bullet->init(shooter, direction, force);

	return bullet;
}

Bullet::Bullet(PhysicsEngine* _pEn) : Moveable(_pEn) {}

Bullet::~Bullet() {}

bool Bullet::init(Shooter* shooter, float direction, float force)
{
	m_shooter = shooter;
	m_direction = direction;
	m_force = force;

	velocity.x = direction * force * 33.3f;

	m_bullettype = Nut;

	return true;
}

void Bullet::update(float dt)
{
	Moveable::update(dt);
	//this->setPositionX(this->getPosition().x + (m_force * m_direction));
	this->getSprite()->setRotation(this->getSprite()->getRotation() + (m_force * m_direction));
}

bool Bullet::onCollision(PhysicsObject* _other, int _myColliderTag)
{
	//g_pLogfile->fLog(L_DEBUG, "other tag: %i<br/>", _other->getTag());
	return false;
}

void Bullet::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

//	Collider* collider = Collider::create(10.0f, 10.0f);
//	this->addComponent(collider);
}

void Bullet::destroy()
{
	if (m_bullettype == Bullettype::Nut)
	{
		auto sound = CocosDenshion::SimpleAudioEngine::getInstance();
		sound->playEffect("sounds/sawyer/Ehit.wav", false, 1.0f, 0.0f, 1.0f);
		this->getParent()->removeChild(this->getSprite());
		this->removeFromParentAndCleanup(true);
		m_shooter->deleteBullet(this);
	}
}

//void Bullet::CheckForCollisions()
//{
//	if (m_pSnail != nullptr)
//	{
//		if (m_pSnail->getColliderComponent()->getCollisionRectangle().intersectsRect(this->getColliderComponent()->getCollisionRectangle()))
//		{
//			m_pSnail->killIt();
//		}
//	}
//	if (m_pSlimeHeap != nullptr)
//	{
//		if (m_pSlimeHeap->getColliderComponent()->getCollisionRectangle().intersectsRect(this->getColliderComponent()->getCollisionRectangle()))
//		{
//			m_pSlimeHeap->killIt();
//		}
//	} 
//	if (m_pMantis != nullptr)
//	{
//		if (m_pMantis->getColliderComponent()->getCollisionRectangle().intersectsRect(this->getColliderComponent()->getCollisionRectangle()))
//		{
//			m_pMantis->applyDamage();
//		}
//	}
//
//	list<Ground*>* physObj = this->getParent()->getPhysicsObjects();
//	list<Ground*> desObj;
//	for (Ground* g : *physObj)
//	{
//			if (g->getGround())
//			{
//				Collider* c = dynamic_cast<Collider*>(g->getComponent("collider"));
//				Collider* c2 = getColliderComponent();
//				if (c->getCollisionRectangle().intersectsRect(getColliderComponent()->getCollisionRectangle()))
//				{
//					desObj.push_back(g);
//				}
//			}
//			
//	}
//	for (list<Ground*>::iterator itr = desObj.begin(); itr != desObj.end();)
//	{
//		this->destroy();
//		itr = desObj.erase(itr);
//	}
//}