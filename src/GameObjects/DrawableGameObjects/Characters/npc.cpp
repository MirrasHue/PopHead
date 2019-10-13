#include "npc.hpp"
#include "Resources/collisionRectData.hpp"
#include "gameData.hpp"
#include "Physics/CollisionBody/collisionBody.hpp"
#include "Resources/spriteSheetData.hpp"

namespace ph {

namespace
{
	constexpr unsigned int movementSpeed = 55;
	constexpr unsigned int hp = 50;
	constexpr unsigned int maxHp = 50;
	const sf::FloatRect posAndSize(
		0,
		0,
		CollisionRectData::HUMAN_WIDTH,
		CollisionRectData::HUMAN_HEIGHT
	);
	constexpr float mass = 25;

	const Animation animation(
		std::array<std::string, 10>{
			"down", "right", "left", "rightUp", "leftUp", "up", "crawlingUp", "dead", "stayingDown", "stayingLeft"
		},
		std::array<sf::IntRect, 10>{
			sf::IntRect(0, 0 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 1 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 2 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 3 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 4 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 5 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 6 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 7 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 0 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT),
			sf::IntRect(0, 2 * SpriteSheetData::NPC_HEIGHT, SpriteSheetData::NPC_WIDTH, SpriteSheetData::NPC_HEIGHT)
		},
		{
			2, 2, 2, 2, 2, 2, 2, 1, 1, 1
		},
		{SpriteSheetData::NPC_TEXTURE_WIDTH, SpriteSheetData::NPC_TEXTURE_HEIGHT},
		sf::seconds(0.30f)
	);
}

Npc::Npc(GameData* gameData, const std::string& name, const std::string& texturePath)
	:Character(gameData, name, gameData->getTextures().get(texturePath), 
		animation, movementSpeed, hp, maxHp, posAndSize, mass, false)
{
	mAnimation.animate(mSprite.mVertexArray.getVertexBuffer());
}

void Npc::updateCurrent(sf::Time delta)
{
	setPosition(mCollisionBody.getFixedPosition());
	mAnimation.animate(mSprite.mVertexArray.getVertexBuffer(), delta);
}

}
