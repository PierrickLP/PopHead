#include "aiManager.hpp" 
#include <algorithm>
#include <cmath>

namespace ph {

Path AIManager::getZombiePath(const sf::Vector2f zombiePosition) const
{
	if(doesZombieSeePlayer(zombiePosition))
		return getPath(zombiePosition, mPlayerPosition);
	else
		return getRandomPath(zombiePosition);
}

void AIManager::registerMapSize(const sf::Vector2u mapSizeInTiles)
{
	mGrid.resize(mapSizeInTiles.y);
	for(auto& row : mGrid) {
		row.resize(mapSizeInTiles.x);
		std::fill(row.begin(), row.end(), false);
	}
}

void AIManager::registerObstacle(const sf::Vector2f collisionBodyPosition)
{
	const unsigned gridPositionX = static_cast<unsigned>(collisionBodyPosition.x) / mSpotSideLength;
	const unsigned gridPositionY = static_cast<unsigned>(collisionBodyPosition.y) / mSpotSideLength;
	mGrid[gridPositionX][gridPositionY] = true;
}

bool AIManager::doesZombieSeePlayer(const sf::Vector2f zombiePosition) const
{
	float legX = std::abs(zombiePosition.x - mPlayerPosition.x);
	float legY = std::abs(zombiePosition.y - mPlayerPosition.y);
	float distanceBetweenZombieAndPlayer = std::hypotf(legX, legY);
	constexpr float maximalDistanceFromWhichZombieSeesPlayer = 200.f;
	return distanceBetweenZombieAndPlayer <= maximalDistanceFromWhichZombieSeesPlayer;
}

Path AIManager::getPath(const sf::Vector2f startPosition, const sf::Vector2f destination) const
{
	return Path();
}

Path AIManager::getRandomPath(const sf::Vector2f startPosition) const
{
	return Path();
}

}