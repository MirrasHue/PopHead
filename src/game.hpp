#pragma once

#include "gameData.hpp"
#include "Audio/Music/musicPlayer.hpp"
#include "Audio/Sound/soundPlayer.hpp"
#include "AI/aiManager.hpp"
#include "Scenes/sceneManager.hpp"
#include "Resources/resourceHolder.hpp"
#include "Terminal/terminal.hpp"
#include "DebugCounter/debugCounter.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace ph {

class Game
{
public:
	Game();

	void run();
	inline auto getGameData() const -> const GameData & { return *(mGameData); };
	Terminal* getTerminal() { return mTerminal.get(); }

private:
	sf::Time correctDeltaTime(sf::Time dt);
	void handleEvents();
	void update(sf::Time dt);

private:
	sf::RenderWindow               mWindow;
	std::unique_ptr<GameData>      mGameData;
	std::unique_ptr<SoundPlayer>   mSoundPlayer;
	std::unique_ptr<MusicPlayer>   mMusicPlayer;
	std::unique_ptr<TextureHolder> mTextures;
	std::unique_ptr<FontHolder>    mFonts;
	std::unique_ptr<AIManager>     mAIManager;
	std::unique_ptr<SceneManager>  mSceneManager;
	std::unique_ptr<Terminal>      mTerminal;
	std::unique_ptr<DebugCounter>  mDebugCounter;
	std::unique_ptr<GUI>           mGui;
};

}
