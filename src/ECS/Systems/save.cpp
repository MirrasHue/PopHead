#include "pch.hpp"
#include "save.hpp"
#include "ECS/Components/charactersComponents.hpp"
#include "ECS/Components/objectsComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"
#include "Renderer/renderer.hpp"

namespace ph::system {

void Save::update(float dt)
{
	using namespace component;

	mRegistry.view<SavePoint, BodyRect>().each([&]
	(auto& save, auto saveBody)
	{
		mRegistry.view<Player, BodyRect, BodyCircle>().each([&]
		(auto, auto playerBody, auto playerCircle)
		{
			if(save.timeSincePlayerSteppedOnIt < 2.f)
			{
				save.timeSincePlayerSteppedOnIt += dt;
				u8 alpha = 255 - Cast<u8>(save.timeSincePlayerSteppedOnIt * 127.f);
				Renderer::submitText("GAME SAVED", "LiberationMono-Bold.ttf", {800.f, 10.f}, 70,
				                     sf::Color(50, 50, 255, alpha), 10, ProjectionType::gui);
			}

			if(intersect(saveBody, playerBody, playerCircle))
			{
				if(!save.isintersectingPlayer)
				{
					save.isintersectingPlayer = true;
					save.timeSincePlayerSteppedOnIt = 0.f;
				}
			}
			else
			{
				save.isintersectingPlayer = false;	
			}
		});
	});
}

}