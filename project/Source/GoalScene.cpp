#include "GoalScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include<assert.h>
#include<vector>

GoalScene::GoalScene()
{
	hImage = LoadGraph("data/image/3Dchara.png");
	assert(hImage != -1);

	bgImage = LoadGraph("data/image/BGgoal.png");
	assert(bgImage != -1);

	gmImage = LoadGraph("data/image/greenmidasi.png");
	assert(gmImage != -1);

	glImage = LoadGraph("data/image/GameClear.png");
	assert(glImage != -1);

	fadeAlpha = 255;

	fonthandle = CreateFontToHandle(NULL, 32, 3);
	blinkTimer = 0;
}

GoalScene::~GoalScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(hImage);
	DeleteGraph(gmImage);
	DeleteGraph(glImage);
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
	DrawExtendGraph(0, 0, 1280, 720, bgImage,TRUE);

	DrawRectRotaGraph(600,150, 0, 0, 1354, 303, 0.75f, 0.0, glImage, TRUE);

	DrawRectRotaGraph(570, 630, 0, 0, 591, 95, 0.75f, 0.0, gmImage, TRUE);
	
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


	blinkTimer++;
	if ((blinkTimer / 45) % 2 == 0)	{
		DrawStringToHandle(460, 610, "Tキー：タイトル", GetColor(255, 255, 255), fonthandle);
	}

	// フェード用黒画面
	if (fadeAlpha > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
