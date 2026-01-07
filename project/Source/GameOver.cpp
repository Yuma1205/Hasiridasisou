#include "GameOver.h"
#include<assert.h>
#include"Player.h"

GameOver::GameOver()
{
	hImage = LoadGraph("data/image/gameover.png");
	assert(hImage > 0);
}

GameOver::~GameOver()
{
}

void GameOver::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
}

void GameOver::Draw()
{
	DrawGraph(200, 100, hImage, TRUE);
	DrawString(200, 200, "‰E–îˆó‚ð‰Ÿ‚µ‚Ä", GetColor(255, 255, 255));
}
