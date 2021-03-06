#pragma once

#include "ECS/entitiesTemplateStorage.hpp"
#include "Resources/resourceHolder.hpp"
#include <entt/entity/registry.hpp>
#include <string>

namespace ph{

class GameData;
class Xml;
class CutSceneManager;

template <typename GuiParser, typename MapParser, typename ObjectsParser, typename AudioParser, typename EnttParser>
class SceneParser
{
public:
	SceneParser(GameData* const gameData, CutSceneManager& cutSceneManager, EntitiesTemplateStorage& templateStorage,
                entt::registry& gameRegistry, const std::string& sceneFileName, TextureHolder&, SystemsQueue&, GUI&, MusicPlayer&, AIManager& aiManager);
private:
	template<typename Parser>
	void parse(GameData* const gameData, const Xml& sceneLinksNode, const std::string& categoryName);

	void parseEcsEntities(const Xml& sceneLinksNode, AIManager& aiManager, EntitiesTemplateStorage& templateStorage, entt::registry& gameRegistry,
                          TextureHolder& textureHolder);

	void parseAmbientLight(const Xml& sceneLinksNode);
	void parseArcadeMode(const Xml& sceneLinksNode, SystemsQueue&, GUI&, AIManager& aiManager, MusicPlayer&, EntitiesTemplateStorage&);
	void parseMap(const Xml& sceneLinksNode, AIManager& aiManager, entt::registry& gameRegistry, EntitiesTemplateStorage& templates, TextureHolder& textures);
	void parseMapObjects(const Xml& sceneLinksNode, AIManager&, entt::registry& gameRegistry, EntitiesTemplateStorage&, CutSceneManager&, SceneManager&, TextureHolder&);
	void parseAudio(const Xml& sceneLinksNode, SoundPlayer&, MusicPlayer&);
};

}
#include "sceneParser.inl"
