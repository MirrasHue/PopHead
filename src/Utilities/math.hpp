#pragma once

#include "Utilities/forceInline.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

namespace ph::Math {

	template <typename T>
	FORCE_INLINE sf::Vector2<T> getUnitVector(const sf::Vector2<T>);

	FORCE_INLINE sf::Vector2f getUnitVector(float angle);
	
	FORCE_INLINE float degreesToRadians(float angle);
	FORCE_INLINE float radiansToDegrees(float angle);

	FORCE_INLINE sf::Vector2u getTwoDimensionalPositionFromOneDimensionalArrayIndex(const unsigned index, const unsigned numberOfColumns);

	FORCE_INLINE bool isPointInsideCircle(const sf::Vector2f point, const sf::Vector2f circlePos, const float radius);

	FORCE_INLINE sf::Vector2f lerp(const sf::Vector2f source, const sf::Vector2f destination, const float speed);

	template <typename T>
	FORCE_INLINE float distanceBetweenPoints(const sf::Vector2<T>& point1, const sf::Vector2<T>& point2);

	template <typename T>
	FORCE_INLINE sf::Vector2<T> abs(const sf::Vector2<T>);

	FORCE_INLINE bool areApproximatelyEqual(float a, float b, float maxApproximation);
	FORCE_INLINE bool areApproximatelyEqual(const sf::Vector2f a, const sf::Vector2f b, float maxApproximation);
}

#include "math.inl"
