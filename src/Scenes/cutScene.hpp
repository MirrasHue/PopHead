#pragma once

#include <SFML/System.hpp>

namespace ph {

class CutScene
{
public:
	CutScene(bool pausesSystems);
	virtual void update(const sf::Time dt) = 0;
	bool isActive() const;
	bool pausesSystems() const { return mPausesSystems; }

protected:
	bool mIsActive;
private:
	bool mPausesSystems;
};

}