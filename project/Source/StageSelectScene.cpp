#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"

StageSelectScene::StageSelectScene()
{
	selectMap=1;

}

StageSelectScene::~StageSelectScene()
{
	
}

void StageSelectScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		selectMap = 2;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		selectMap = 1;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		SceneManager::SetNextStage(selectMap);
		SceneManager::ChangeScene("PLAY");
	}

	if (CheckHitKey(KEY_INPUT_0)) {
		SceneManager::ChangeScene("GOAL");
	}
	if (CheckHitKey(KEY_INPUT_9)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
}

void StageSelectScene::Draw()
{
	DrawString(300, 50, "STAGE SELECT", GetColor(255, 255, 255));

	const char* mapName[2] = {
		"NORMAL",
		"HARD"
	};

	int boxW = 550;
	int boxH = 500;
	int y =100;

	for (int i = 0; i < 2; i++)
	{
		int x = 50 + i * 650;
		int mapNumber = i + 1;

		bool isSelect = (selectMap == mapNumber);

		DrawBox(
			x, y, x + boxW, y + boxH,
			GetColor(255, 255, 255), TRUE
		);

		//˜gü
		int borderThikness = isSelect ? 6 : 2;
		for (int t = 0; t < borderThikness; t++) {
			DrawBox(x-t, y-t, 
				x + boxW+t, y + boxH+t,
				isSelect ? GetColor(255, 255, 0) :
				GetColor(0, 0, 0),
				FALSE);
		}
		//•¶Žš’†‰›Šñ‚¹
		int strW = GetDrawStringWidth(mapName[i], -1);
		int strH = 32;

		DrawString(
			x + (boxW - strW) / 2,
			y + (boxH - strH) / 2,
			mapName[i],
			isSelect ? GetColor(255, 0, 0) : GetColor(0, 0, 0)
		);
	}

	DrawString(180, 620, "© ¨ : ‘I‘ð  ENTER : Œˆ’è", GetColor(200, 200, 200));
}
