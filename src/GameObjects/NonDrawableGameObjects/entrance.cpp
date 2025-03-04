#include "entrance.hpp"
#include "Utilities/rect.hpp"
#include "Scenes/sceneManager.hpp"
#include "GameObjects/DrawableGameObjects/Characters/player.hpp"
#include "Logs/logs.hpp"

namespace ph{

Entrance::Entrance(SceneManager& sceneManager, const std::string filepath, const std::string name,
	const sf::Vector2f size, const sf::Vector2f position, const sf::Vector2f positionToGo)
	:GameObject(name)
	,mSceneManager(sceneManager)
	,mEntranceArea(size)
	,mFilepath(filepath)
	,mPositionToGo(positionToGo)
	,mHasPositionToGo(true)
{
	mEntranceArea.setPosition(position);
}

Entrance::Entrance(SceneManager& sceneManager, const std::string filepath, const std::string name,
	const sf::Vector2f size, const sf::Vector2f position)
	:GameObject(name)
	, mSceneManager(sceneManager)
	, mEntranceArea(size)
	, mFilepath(filepath)
	, mHasPositionToGo(false)
{
	mEntranceArea.setPosition(position);
}

void Entrance::updateCurrent(const sf::Time delta)
{
	auto* standingObjects = mRoot->getChild("LAYER_standingObjects");
	auto* playerGameObject = standingObjects->getChild("player");
	if(playerGameObject == nullptr)
		return;
	auto* player = dynamic_cast<Player*>(playerGameObject);
	if (FloatRect::doPositiveRectsIntersect(player->getGlobalBounds(), mEntranceArea.getGlobalBounds()))
	{
		if (mHasPositionToGo)
			mSceneManager.replaceScene(mFilepath, mPositionToGo);
		else
			mSceneManager.replaceScene(mFilepath);
	}
}

}