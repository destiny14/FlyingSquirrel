#ifndef __AIRCURRENT_H__
#define __AIRCURRENT_H__

#define TAG_AIR 12365798

#include "Ground.h"

class MainLayer;

class Aircurrent : public Node
{
public:
	static Aircurrent* create(MainLayer* _layer, Point _dir, Size _size);
	void update(float _dt) override;
	Point getDirection() { return m_dir; }
	Size getSize() { return dynamic_cast<Collider*>(this->getComponent("collider"))->getCollisionRectangle().size; }
private:
	Aircurrent();

	MainLayer* m_pLayer;
	Point m_dir;
};

#endif