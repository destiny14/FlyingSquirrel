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

		const Point p = getPosition();
		const Point desiredMove = velocity * tmp;
		Point move = desiredMove;

		bool collision = false;
		int checks = 0;
		do {
			setPosition(p + move);
			collision = m_pEngine->checkForBlockingCollision(this);
			checks++;
			move = desiredMove - (move / MAX_INTERPOLATIONCHECKS) * checks;		
		} while (!collision && checks < MAX_INTERPOLATIONCHECKS);

		if (collision)
		{
			setPosition(p);
			break;
		}

		tmpDt -= tmp;
	}
}