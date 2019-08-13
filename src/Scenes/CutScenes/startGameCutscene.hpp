#pragma once

#include "Scenes/cutScene.hpp"
#include <SFML/System.hpp>
#include "GameObjects/DrawableGameObjects/Characters/npc.hpp"

namespace ph {

class Camera;
class SoundPlayer;
class MusicPlayer;
class GUI;
class Car;
class GameData;

class StartGameCutScene : public CutScene
{
public:
	StartGameCutScene(GameObject& root, Camera&, SoundPlayer&, MusicPlayer&, GUI& gui, GameData* const);
	void update(const sf::Time delta) override;

private:
	void updateNarrativeSubtitles(const float cutsceneTimeInSeconds, Car& car);
	void createPlayer();
	void rotatePlayer();
	void updateSpeech(const float cutsceneTimeInSeconds);
	void rotateAround(const float cutsceneTimeInSeconds);
	void lookSouth();
	void sayFuck(const float cutsceneTimeInSeconds);
	void spawnZombieNearPlayer();
	void createZombie(const sf::Vector2f position);

private:
	Camera& mCamera;
	SoundPlayer& mSoundPlayer;
	MusicPlayer& mMusicPlayer;
	GUI& mGui;
	GameData* const mGameData;
	sf::Clock mClock;
	bool mHasStartedToSlowDown;
	bool mHasChangedTheMusic;
	bool mWasNpcCreated;
	bool mHasPlayerTurnedToNpc;
	bool mWereZombieSpawned;
};

}