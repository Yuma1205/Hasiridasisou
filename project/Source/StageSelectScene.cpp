#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"
#include <cstring>

StageSelectScene::StageSelectScene()
{
    selectMap = 1;

    // キー状態の初期化
    memset(keyOld, 0, sizeof(keyOld));

    fontHandle = CreateFontToHandle("MS ゴシック", 64, -1, DX_FONTTYPE_ANTIALIASING);
    // コンストラクタで作成
    titleFontHandle = CreateFontToHandle("ＭＳ ゴシック", 32, -1, DX_FONTTYPE_ANTIALIASING);
}

StageSelectScene::~StageSelectScene()
{
    DeleteFontToHandle(fontHandle);
    DeleteFontToHandle(titleFontHandle);

}

// 定数
static const int MAX_STAGE = 3;

void StageSelectScene::Update()
{
    char keyNow[256];
    GetHitKeyStateAll(keyNow);

    // 左右移動
    if (keyNow[KEY_INPUT_RIGHT] && !keyOld[KEY_INPUT_RIGHT]) {
        selectMap++;
        if (selectMap > MAX_STAGE) selectMap = MAX_STAGE;
    }

    if (keyNow[KEY_INPUT_LEFT] && !keyOld[KEY_INPUT_LEFT]) {
        selectMap--;
        if (selectMap < 1) selectMap = 1;
    }

    // 決定
    if (keyNow[KEY_INPUT_SPACE] && !keyOld[KEY_INPUT_SPACE]) {
        SceneManager::SetNextStage(selectMap);
        SceneManager::ChangeScene("PLAY");
    }

    // デバッグ用シーン切替
    if (keyNow[KEY_INPUT_0] && !keyOld[KEY_INPUT_0]) {
        SceneManager::ChangeScene("GOAL");
    }
    if (keyNow[KEY_INPUT_9] && !keyOld[KEY_INPUT_9]) {
        SceneManager::ChangeScene("GAMEOVER");
    }

    // キー状態更新
    memcpy(keyOld, keyNow, sizeof(keyNow));
}

void StageSelectScene::Draw()
{
    // Draw内で描画
    DrawStringToHandle(300, 50,"STAGE SELECT",GetColor(255, 255, 255),
        titleFontHandle );


    const char* mapName[MAX_STAGE] = {
        "EASY",
        "NORMAL",
        "HARD"
    };

    int boxW = 350;
    int boxH = 500;
    int y = 100;
    int screenW = 1280;

    int margin = (screenW - boxW * MAX_STAGE) / (MAX_STAGE + 1);

    for (int i = 0; i < MAX_STAGE; i++)
    {
        int x = margin + i * (boxW + margin);
        int mapNumber = i + 1;
        bool isSelect = (selectMap == mapNumber);

        // 背景ボックス
        DrawBox(x, y, x + boxW, y + boxH, GetColor(255, 255, 255), TRUE);

        // 枠線
        int borderThikness = isSelect ? 6 : 2;
        for (int t = 0; t < borderThikness; t++) {
            DrawBox(
                x - t, y - t,
                x + boxW + t, y + boxH + t,
                isSelect ? GetColor(255, 255, 0) : GetColor(0, 0, 0),
                FALSE
            );
        }

        // 文字中央寄せ
        int strW = GetDrawStringWidthToHandle(mapName[i], -1,fontHandle);
        int fontSize = 64;

        int drawX = x + (boxW - strW) / 2;
        int drawY = y + (boxH - fontSize) / 2;
        DrawStringToHandle(
            drawX,drawY,
            mapName[i],
            isSelect ? GetColor(255, 0, 0) : GetColor(0, 0, 0),
            fontHandle
        );
    }

    DrawStringToHandle(180, 620, "← → : 選択  SPACE : 決定", GetColor(200, 200, 200),titleFontHandle);
}

