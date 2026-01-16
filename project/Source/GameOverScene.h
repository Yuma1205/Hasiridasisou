#pragma once
#include "../Library/SceneBase.h"

class GameOverScene : public SceneBase
{
private:
	int GameOver;
	int bgImage;
	int hImage;
	int dImage;
	int smImage;
	int gmImage;

	int playerX;
	int playerY;

	bool direction;

	int fadeAlpha;

public:
	GameOverScene();
	~GameOverScene();

	void Update()override;
	void Draw()override;
};

