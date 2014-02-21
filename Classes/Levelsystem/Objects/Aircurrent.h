#ifndef __AIRCURRENT_H__
#define __AIRCURRENT_H__

#include "Ground.h"

class MainLayer;

class Aircurrent : public Node
{
public:
	static Aircurrent* create(MainLayer* _layer, Point _dir, Size _size);
	void update(float _dt) override;
private:
	Aircurrent();

	MainLayer* m_pLayer;
	Point m_dir;
};

#endif