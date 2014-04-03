#include "Moveable.h"
#include "MainLayer.h"

USING_NS_CC;
using namespace std;

Moveable::Moveable(PhysicsEngine* _pEn) : Ground(_pEn)
{
	m_grounded = false;
	m_gravity = -600.0f;

	//Create Colliders
	up = new AABBCollider();
	up->setTag(0);
	bot = new AABBCollider();
	bot->setTag(1);
	left = new AABBCollider();
	left->setTag(2);
	right = new AABBCollider();
	right->setTag(3);
	collider = new CompoundCollider();
	m_topHitGround = nullptr;
	//Build compound Collider
	collider->addCollider(up);
	collider->addCollider(bot);
	collider->addCollider(left);
	collider->addCollider(right);
	collider->setPhysicsObject(this);
}

Moveable::~Moveable()
{
}

void Moveable::setGrounded(bool grounded)
{
	m_grounded = grounded;
}

void Moveable::update(float dt)
{
	if (!isGrounded())
	{
		velocity.y += m_gravity * dt;
	}
	else if (velocity.y <= 0.0f)
	{
		velocity.y = -1.0f;
	}
	
	bool botAfterTop = m_botAfterTop;
	m_botAfterTop = false;
	
	m_grounded = false;
	Ground::update(dt);

	if (botAfterTop && !m_botAfterTop)
	{
		m_topHitGround = nullptr;
	}
}

bool Moveable::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (_other->getTag() != TAG_GROUND) return false;

	if (myColliderTag == up->getTag())
	{
		m_botAfterTop = false;
		m_topHitGround = _other;
	}
	else if (myColliderTag == left->getTag())
	{
		m_botAfterTop = false;
		m_topHitGround = _other;
	}
	else if (myColliderTag == right->getTag())
	{
		m_botAfterTop = false;
		m_topHitGround = _other;
	}
	else if (myColliderTag == bot->getTag())
	{
		if (m_topHitGround == nullptr || m_topHitGround != _other)
		{
			m_topHitGround = nullptr;
			m_botAfterTop = false;
			m_grounded = true;
			return true;
		}
		else
		{
			m_botAfterTop = true;
		}
	}

	return false;
}
void Moveable::setSize(float _w, float _h)
{
	size = Size(_w, _h);
	up->setBoundingRect(Rect(		10,			_h - 5,		_w - 20,	5				));
	bot->setBoundingRect(Rect(		10,			10,			_w - 20,	5				));
	left->setBoundingRect(Rect(		0,			10,			_w * 0.5f,	_h -10			));
	right->setBoundingRect(Rect(	_w * 0.5f,	10,			_w * 0.5f,	_h -10  		));
}

void Moveable::setSizeToTexture()
{
	if (getTexture() == nullptr) return;

	setSize(getTexture()->getBoundingBox().size.width, getTexture()->getBoundingBox().size.height);
}