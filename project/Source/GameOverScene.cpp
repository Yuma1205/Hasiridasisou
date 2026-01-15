#include "GameOverScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include<assert.h>

GameOverScene::GameOverScene()
{
	bgImage = LoadGraph("data/image/yoru.png");
	assert(bgImage != -1);
	
	hImage = LoadGraph("data/image/Dead.png");
	assert(hImage != -1);

	dImage = LoadGraph("data/image/gameover.png");
	assert(dImage != -1);

	playerX = 300;
    playerY = 400;
	direction = false;

	fadeAlpha = 255;
}

GameOverScene::~GameOverScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(hImage);
	DeleteGraph(dImage);
}

void GameOverScene::Update()
{
	// フェードイン
	if (fadeAlpha > 0) {
		fadeAlpha -= 5;   // ← 数値を変えると速さ調整
		if (fadeAlpha < 0) fadeAlpha = 0;
		return; // フェード中はキー入力を無効にする
	}

	if (CheckHitKey(KEY_INPUT_T) || CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}

	if (CheckHitKey(KEY_INPUT_R)) {
		SceneManager::ChangeScene("PLAY");
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);

	DrawGraph(100, 100, dImage, TRUE);

	// 倒れたキャラ
	DrawGraph(playerX, playerY, hImage, TRUE);

	DrawString(200, 600, "Tキー：タイトル", GetColor(255, 255, 255));
	DrawString(400, 600, "Rキー：リトライ", GetColor(255, 255, 255));

	// フェード用黒画面
	if (fadeAlpha > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
