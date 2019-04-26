#include "object.hpp"
#include "Base/gameData.hpp"

using PopHead::World::Entity::Object;


Object::Object(PopHead::Base::GameData* gameData, std::string name, PopHead::Renderer::LayerID layerID)
:Entity(PopHead::World::EntityType::object, gameData, name)
,mLayerID(layerID)
{
    mGameData->getRenderer().addObject(this, layerID);
}

void Object::onCollision(Object&)
{
}

void Object::setVisibility(bool visibility) 
{ 
	mVisibility = visibility;

	std::function<void(bool)> func = [=](bool visibility) {
		this->mVisibility = visibility;
	};
	forEachChildWhichIsObject(func, visibility);
}

void Object::setPosition(sf::Vector2f pos) 
{
	mPosition = pos;
}

void Object::move(sf::Vector2f motion)
{
	mPosition.x += motion.x;
	mPosition.y += motion.y;
}

void Object::setScale(sf::Vector2f scale) { mScale = scale; }

void Object::setRotation(float angle) { mRotation = angle; }

sf::Vector2f Object::getPosition() const { return mPosition; }

sf::Vector2f Object::getScale() const { return mScale; }

float Object::getRotation() const { return mRotation; }

auto Object::getLayerID() const -> PopHead::Renderer::LayerID { return mLayerID; }

bool Object::getVisibility() const { return mVisibility; }
