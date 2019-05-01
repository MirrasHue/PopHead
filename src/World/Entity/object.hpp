#ifndef POPHEAD_WORLD_OBJECT_H_
#define POPHEAD_WORLD_OBJECT_H_

#include <SFML/Graphics.hpp>
#include <functional>

#include "World/Entity/entity.hpp"
#include "Renderer/layerID.hpp"

namespace PopHead {
namespace World {
namespace Entity {


class Object : public Entity, public sf::Drawable
{
public:
    Object(Base::GameData*, std::string name, Renderer::LayerID);

    void setVisibility(bool visibility);
    virtual void setPosition(sf::Vector2f, bool recursive);
	virtual void move(sf::Vector2f);
    virtual void setScale(sf::Vector2f);
    virtual void setRotation(float angle);
    virtual void rotate(float angle);

	auto getPosition() -> sf::Vector2f const { return mPosition; }
	auto getScale() -> sf::Vector2f const { return mScale; }
	float getRotation() const { return mRotation; }
	auto getLayerID() const -> PopHead::Renderer::LayerID { return mLayerID; }
	bool getVisibility() const { return mVisibility; }

private:
	template <typename T>
	void forEachChildWhichIsObject(std::function<void(Object*, T)> func, T param);

protected:
    sf::Vector2f mPosition;
    sf::Vector2f mScale;
    float mRotation;
    bool mVisibility;
    const Renderer::LayerID mLayerID;
};


}}}

#include "object.inl"

#endif // !POPHEAD_WORLD_OBJECT_H_
