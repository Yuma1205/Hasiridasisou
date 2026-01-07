#pragma once
#include "../Library/SceneBase.h"

class GameOverScene : public SceneBase
{
private:
	int GameOver;
public:
	GameOverScene();
	~GameOverScene();

	void Update()override;
	void Draw()override;
};

