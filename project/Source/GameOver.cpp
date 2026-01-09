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
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
}

void GameOver::Draw()
{
	DrawGraph(100, 100, hImage, TRUE);
	DrawString(200, 200, "ENTER‚ð‰Ÿ‚µ‚Ä", GetColor(255, 255, 255));
}
