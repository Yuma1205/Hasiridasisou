#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"

StageSelectScene::StageSelectScene()
{
	selectStage = 1;

}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		selectStage++;
		if (selectStage > 2)selectStage = 2;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		selectStage--;
		if (selectStage < 1)selectStage = 1;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		SceneManager::SetNextStage(selectStage);
		SceneManager::ChangeScene("PLAY");
	}
}

void StageSelectScene::Draw()
{
	DrawString(200, 100, "STAGE SELECT", GetColor(255, 255, 255));

	for (int i = 1; i <= 2; i++)
	{
		int color = (i == selectStage)
			? GetColor(255, 255, 0)
			: GetColor(255, 255, 255);

		DrawFormatString(220, 150 + i * 40, color,
			"STAGE %d", i);
	}

	DrawString(180, 320, "© ¨ : ‘I‘ð  ENTER : Œˆ’è", GetColor(200, 200, 200));
}
