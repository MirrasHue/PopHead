#include "map.hpp"
#include "Base/gameData.hpp"
#include "Utilities/debug.hpp"
#include "Utilities/csv.hpp"
#include "Utilities/math.hpp"

ph::Map::Map(GameData* gameData, std::string name, float scale)
	:Object(gameData, name, LayerID::floorEntities)
{
	// TODO: Scale tiles? (scale funtion paramiter)
}

void ph::Map::loadFromFile(const std::string& filename)
{
	Xml document;
	document.loadFromFile(filename);
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

	const std::vector<Xml> tilesetNodes = mapNode.getChildren("tileset");
	if (tilesetNodes.size() == 0)
		PH_LOG(LogType::Warning, "Map doesn't have any tilesets: " + filename);
	TilesetsData tilesets = getTilesetsData(tilesetNodes);

	const std::vector<Xml> layerNodes = mapNode.getChildren("layer");
	if (layerNodes.size() == 0)
		PH_LOG(LogType::Warning, "Map doesn't have any layers: " + filename);
	mTiles.reserve(mapSize.x * mapSize.y * layerNodes.size());
	for (const Xml& layerNode : layerNodes) {
		const Xml dataNode = layerNode.getChild("data");
		const std::string encoding = dataNode.getAttribute("encoding").toString();
		if (encoding != "csv")
			PH_EXCEPTION("Used unsupported data encoding: " + encoding);

		const std::vector<unsigned> values = Csv::toUnsigneds(dataNode.toString());
		loadTiles(values, tilesets, mapSize, tileSize);
	}
}

ph::Map::TilesetsData ph::Map::getTilesetsData(const std::vector<Xml>& tilesetNodes) const
{
	/*
		TODO:
		What if tileset is self-closing tag (firstgid and source is defined, but he is in different file)?
		- (BEST) Do something with Xml impl to check if there is source attribute defined? ->
			* return iterator in getAttribute(name)?
			* return std::pair in getAttribute(name)?
			* return struct in getAttribute(name)?
			* make output argument?
			* make method hasAttribute(name)? -> bad performance (double find or hard impl based on temp buffer)
		- Assume that there is not such? -> Maybe it would be better to just allow them.
		- Try to find it and catch corresponding exception by checking error message
			(much better: define proper exception type in Xml impl)?
	*/
	TilesetsData tilesets;
	tilesets.sources.reserve(tilesetNodes.size());
	tilesets.columnsCounts.reserve(tilesetNodes.size());
	tilesets.globalIds.reserve(tilesetNodes.size());
	tilesets.tileCounts.reserve(tilesetNodes.size());
	for (std::size_t i = 0; i < tilesetNodes.size(); ++i) {
		tilesets.columnsCounts.push_back(tilesetNodes[i].getAttribute("columns").toUnsigned());
		tilesets.globalIds.push_back(tilesetNodes[i].getAttribute("firstgid").toUnsigned());
		tilesets.tileCounts.push_back(tilesetNodes[i].getAttribute("tilecount").toUnsigned());

		const Xml imageNode = tilesetNodes[i].getChild("image");
		tilesets.sources.push_back(imageNode.getAttribute("source").toString());
		tilesets.sources[i] = Path::toFilename(tilesets.sources[i], '/');
	}
	return tilesets;
}

void ph::Map::loadTiles(const std::vector<unsigned>& values,
						const TilesetsData& tilesets,
						sf::Vector2u mapSize,
						sf::Vector2u tileSize)
{
	for (std::size_t i = 0; i < values.size(); ++i) {
		if (hasTile(values[i])) {
			const std::size_t j = findTilesetIndex(values[i], tilesets);
			if (j == std::string::npos) {
				PH_LOG(LogType::Warning, "It was not possible to find tileset for value " + values[i]);
				continue;
			}

			sf::Vector2u tilePosition = Math::toTwoDimensional(values[i] - tilesets.globalIds[j], tilesets.columnsCounts[j]);
			tilePosition.x *= tileSize.x;
			tilePosition.y *= tileSize.y;
			const sf::IntRect tileRect(
				static_cast<sf::Vector2i>(tilePosition),
				static_cast<sf::Vector2i>(tileSize)
			);
			sf::Sprite tile(mGameData->getTextures().get(pathToMapTextures + tilesets.sources[j]), tileRect);
			sf::Vector2f position(Math::toTwoDimensional(i, mapSize.x));
			position.x *= tileSize.x;
			position.y *= tileSize.y;
			tile.setPosition(position);
			// TODO: Scale tile? (scale funtion paramiter)
			mTiles.push_back(tile);
		}
	}
}

std::size_t ph::Map::findTilesetIndex(unsigned value, const TilesetsData& tilesets) const
{
	for (std::size_t i = 0; i < tilesets.globalIds.size(); ++i) {
		const unsigned lastGlobalTileIdInCurrentTileset = tilesets.globalIds[i] + tilesets.tileCounts[i] - 1;
		if (value >= tilesets.globalIds[i] && value <= lastGlobalTileIdInCurrentTileset) 
			return i;
	}
	return std::string::npos;
}

void ph::Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const sf::Sprite& sprite : mTiles)
		target.draw(sprite, states);
}
