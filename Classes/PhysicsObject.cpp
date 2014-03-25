#include "PhysicsObject.h"
#include "PhysicsEngine.h"

PhysicsObject::PhysicsObject(PhysicsEngine* _engine)
{
	m_pEngine = _engine;
	m_pEngine->addPhysicsObject(this);
}

void PhysicsObject::update(float _dt)
{
	Node::update(_dt);

	if (velocity == Point::ZERO) return;

	float tmpDt = _dt;

	while (tmpDt > 0.0f)
	{
		float tmp = tmpDt > MAX_MOVEINTERVALL ? MAX_MOVEINTERVALL : tmpDt;
		tmpDt -= tmp;

		const Point oldPosition = getPosition();
		const Point desiredMove = velocity * tmp;
		Point move = desiredMove;

		bool col = false;
		int checks = 0;
		do {
			setPosition(oldPosition + move);

			move = desiredMove * (1.0f - (checks / MAX_INTERPOLATIONCHECKS));
			++checks;
		} while (col = m_pEngine->checkForBlockingCollision(this) && checks < MAX_INTERPOLATIONCHECKS);

		if (col && checks < MAX_INTERPOLATIONCHECKS)
		{
			setPosition(oldPosition);
		}

	}
}

void PhysicsObject::removeFromParentAndCleanup(bool _b)
{
	Node::removeFromParentAndCleanup(_b);
	m_pEngine->removePhysicsObject(this);
}