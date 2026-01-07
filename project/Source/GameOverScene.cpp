#include "GameOverScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}

	if (CheckHitKey(KEY_INPUT_R)) {
		SceneManager::ChangeScene("PLAY");
	}
}

void GameOverScene::Draw()
{
	DrawString(200, 100, "Tキー：タイトル", GetColor(255, 255, 255));
	DrawString(200, 200, "Rキー：リトライ", GetColor(255, 255, 255));

}
