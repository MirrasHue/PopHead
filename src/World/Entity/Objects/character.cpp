#include "character.hpp"

#include <iostream>

using PopHead::World::Entity::Character;

Character::Character(PopHead::Base::GameData* gameData, std::string name, PopHead::World::Animation animation,
                     unsigned int movementSpeed, unsigned int HP, unsigned int maxHP)
:Object(gameData, name, Renderer::LayerID::kinematicEntities)
,mHP(HP)
,mMaxHP(maxHP)
,mMovementSpeed(movementSpeed)
,mMotion()
,mAnimation(animation)
{
}

void Character::atack()
{

}

void Character::onCollision(Object&)
{

}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Character::getMaxHP() const { return mMaxHP; }

unsigned int Character::getHP() const { return mHP; }

sf::Sprite& Character::getSprite() { return mSprite; }

/*auto Character::getEquipment() const -> const Equipment&
{}*/

/*auto Character::getCurrentWeapon() const -> const Weapon&
{}*/

/*auto Character::getExperienceManager() const -> const ExperienceManager&
{}*/
