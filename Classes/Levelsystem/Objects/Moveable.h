#ifndef __MOVEABLE_H__
#define __MOVEABLE_H__

#include "cocos2d.h"
#include "LevelLayer.h"
#include "Ground.h"

USING_NS_CC;

class Moveable : public Ground
{
public:
	// static create (char*)
	//
	// erstellt ein neues Objekt vom Typ Moveable
	static Moveable* create(char* filename, LevelLayer* parent);

	Moveable();
	~Moveable();

	// setAffectedByGravity(bool)
	//
	// bestimmt, ob das Objekt von Gravitation beeinflusst wird
	void setAffectedByGravity(bool affectedByGravity);
	bool getAffectedByGrafity();

	// getGrounded()
	//
	// bestimmt, ob sich das Objekt auf dem Boden befindet
	bool getGrounded();

	void setParent(LevelLayer* parent);
	LevelLayer* getParent();

	virtual void update(float dt);
private:
	void CheckForCollisions();
	bool m_affectedByGravity;
	bool m_grounded;
	LevelLayer* m_parent;
	float m_gravity;
	float m_velocity;
};

#endif // !__MOVEABLE_H__
