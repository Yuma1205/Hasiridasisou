#include "GoalScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include<assert.h>

GoalScene::GoalScene()
{
	hImage = LoadGraph("data/image/3Dchara.png");
	assert(hImage != -1);

	bgImage = LoadGraph("data/image/BGgoal.png");
	assert(bgImage != -1);

	fadeAlpha = 255;
}

GoalScene::~GoalScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(hImage);
}

void GoalScene::Update()
{
	// フェードイン
	if (fadeAlpha > 0) {
		fadeAlpha -= 5;   // ← 数値を変えると速さ調整
		if (fadeAlpha < 0) fadeAlpha = 0;
		return; // フェード中はキー入力を無効にする
	}

	if (CheckHitKey(KEY_INPUT_T)||CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void GoalScene::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);
	DrawRectRotaGraph(
		600,
		400,
		0, 0,           // 切り取り開始
		1024, 1536,     // 元画像サイズ
		0.25f,          // 縮小率
		0.0,
		hImage,
		TRUE
	);


	
	DrawString(200, 600, "Tキー：タイトル", GetColor(255, 255, 255));

	// フェード用黒画面
	if (fadeAlpha > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
