#include "map.hpp"
#include "Base/gameData.hpp"
#include "Utilities/xml.hpp"
#include "Utilities/csv.hpp"
#include "Utilities/math.hpp"

using PopHead::World::Entity::Map;
using PopHead::Utilities::Xml;

Map::Map(PopHead::Base::GameData* gameData, std::string name, const std::string& xmlFilename, float scale)
	: Object(gameData, name, Renderer::LayerID::floorEntities)
{
	Xml document;
	document.loadFromFile(xmlFilename);

	const Xml mapNode = document.getChild("map");
	const std::string orientation = mapNode.getAttribute("orientation").toString();
	if (orientation != "orthogonal")
		PH_EXCEPTION("Used unsupported map orientation: " + orientation);
	const std::string infinite = mapNode.getAttribute("infinite").toString();
	if (infinite != "0")
		PH_EXCEPTION("Infinite maps are not supported");
	const sf::Vector2u mapSize(
		mapNode.getAttribute("width").toUnsigned(),
		mapNode.getAttribute("height").toUnsigned()
	);
	const sf::Vector2u tileSize(
		mapNode.getAttribute("tilewidth").toUnsigned(),
		mapNode.getAttribute("tileheight").toUnsigned()
	);

	const Xml tilesetNode = mapNode.getChild("tileset");
	const unsigned tilesetColumns = tilesetNode.getAttribute("columns").toUnsigned();

	const Xml imageNode = tilesetNode.getChild("image");
	std::string source = imageNode.getAttribute("source").toString();
	source = Utilities::Path::toFilename(source, '/');

	// TODO: What if there are no layers? Change Xml impl or just do something here?
	const std::vector<Xml> layerNodes = mapNode.getChildren("layer");
	// TODO: Just use resize and replace push_back with [] in below loop?
	mSprites.reserve(mapSize.x * mapSize.y * layerNodes.size());
	for (const Xml& layerNode : layerNodes) {
		const Xml dataNode = layerNode.getChild("data");
		const std::string encoding = dataNode.getAttribute("encoding").toString();
		if (encoding != "csv")
			PH_EXCEPTION("Used unsupported data encoding: " + encoding);
		const std::vector<unsigned> values = Utilities::Csv::toUnsigneds(dataNode.toString());
		for (std::size_t i = 0; i < values.size(); ++i) {
			if (values[i]) {
				sf::Vector2u tilePosition = Utilities::Math::toTwoDimensional(values[i] - 1, tilesetColumns);
				tilePosition.x *= tileSize.x;
				tilePosition.y *= tileSize.y;
				const sf::IntRect tileRect(
					static_cast<sf::Vector2i>(tilePosition),
					static_cast<sf::Vector2i>(tileSize)
				);
				// TODO: Move map resources path to some better place or make it a static const for example?
				sf::Sprite sprite(mGameData->getTextures().get("resources/textures/map/" + source), tileRect);
				sf::Vector2f position(Utilities::Math::toTwoDimensional(i, mapSize.x));
				position.x *= tileSize.x;
				position.y *= tileSize.y;
				sprite.setPosition(position);
				// TODO: Scale sprite? (scale funtion paramiter)
				mSprites.push_back(sprite);
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const sf::Sprite& sprite : mSprites)
		target.draw(sprite, states);
}
