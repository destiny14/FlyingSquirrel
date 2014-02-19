#ifndef __MOVEABLE_H__
#define __MOVEABLE_H__

#include "cocos2d.h"
#include "LevelLayer.h"
#include "Ground.h"
#include "Layers\MainLayer.h"
#include <list>

USING_NS_CC;

class Moveable : public Ground
{
public:
	// static create (char*)
	//
	// erstellt ein neues Objekt vom Typ Moveable
	static Moveable* create(char* filename, MainLayer* parent);

	Moveable();
	~Moveable();

	void updateCollider();
	void addVelocity(float _x, float _y);
	void setVelocityX(float _x);
	float getVelocityX();

	// setAffectedByGravity(bool)
	//
	// bestimmt, ob das Objekt von Gravitation beeinflusst wird
	void setAffectedByGravity(bool affectedByGravity);
	bool getAffectedByGrafity();

	// getGrounded()
	//
	// bestimmt, ob sich das Objekt auf dem Boden befindet
	bool getGrounded();

	void setParent(MainLayer* parent);
	MainLayer* getParent();

	virtual void update(float dt, bool overwriteCollisionCheck = false);
protected:
	void setGrounded(bool);
private:
	void CheckForCollisions();
	bool m_affectedByGravity;
	bool m_grounded;
	MainLayer* m_parent;
	float m_gravity;
	Point m_velocity;
};

#endif // !__MOVEABLE_H__
