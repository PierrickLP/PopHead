#pragma once 
 
#include "Scenes/cutScene.hpp"

namespace ph { 

class SceneManager;
class GUI;

class SubtitlesBeforeStartGameCutscene : public CutScene
{
public:
	SubtitlesBeforeStartGameCutscene(GameObject& root, SceneManager&, GUI& gui);

	void update(sf::Time delta) override;

private:
	void endCutscene();

private:
	SceneManager& mSceneManager;
	GUI& mGui;
	sf::Clock mClock;
	int mTimesPressedSkip;
};

} 
