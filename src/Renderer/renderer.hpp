#pragma once

#include "Utilities/rect.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace sf {
	class Drawable;
	class RenderWindow;
}

namespace ph {

class DebugCounter;
class Camera;
class Texture;
class Shader;

namespace Renderer
{
	void init(unsigned screenWidth, unsigned screenHeight);
	void restart(unsigned screenWidth, unsigned screenHeight);
	void shutDown();
	
	void beginScene(Camera&);
	void endScene(sf::RenderWindow& window, DebugCounter&);

	void submitQuad(const Texture*, const IntRect* textureRect, const sf::Color*, const Shader* shader,
	                sf::Vector2f position, sf::Vector2f size, unsigned char z, float rotation, bool blocksLight);

	void submitLine(sf::Color, const sf::Vector2f positionA, const sf::Vector2f positionB, float thickness = 1.f);

	void submitLine(sf::Color colorA, sf::Color colorB,
	                const sf::Vector2f positionA, const sf::Vector2f positionB, float thickness = 1.f);

	void submitPoint(sf::Vector2f position, sf::Color, unsigned char z, float size = 1.f);

	void submitLight(sf::Color color, sf::Vector2f position, float startAngle, float endAngle,
	                 float attenuationAddition, float attenuationFactor, float attenuationSquareFactor);

	void submitSFMLObject(const sf::Drawable&);

	void setAmbientLightColor(sf::Color);

	void onWindowResize(unsigned width, unsigned height);
};

}
