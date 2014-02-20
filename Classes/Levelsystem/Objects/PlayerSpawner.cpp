#include "PlayerSpawner.h"

PlayerSpawner::PlayerSpawner(Point spawn)
{
	setSpawnPosition(spawn);
}

PlayerSpawner::~PlayerSpawner() {}

void PlayerSpawner::setSpawnPosition(Point spawn)
{
	m_spawnPosition = spawn;
}

void PlayerSpawner::setSpawnPosition(float x, float y)
{
	m_spawnPosition = Point(x, y);
}

Point PlayerSpawner::getSpawnPosition()
{
	return m_spawnPosition;
}