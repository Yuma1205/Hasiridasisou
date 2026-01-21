#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include <cstring>
#include "../Library/Trigger.h"


StageSelectScene::StageSelectScene()
{
    selectMap = 2;

    fontHandle = CreateFontToHandle("MS ゴシック", 64, -1, DX_FONTTYPE_ANTIALIASING);
    // コンストラクタで作成
    titleFontHandle = CreateFontToHandle("ＭＳ ゴシック", 32, -1, DX_FONTTYPE_ANTIALIASING);

    hBackGround = LoadGraph("data/image/TitleBackGround2.png");

    GetGraphSize(hBackGround, &bgWidth, NULL);

    scrollX = 0;
}

StageSelectScene::~StageSelectScene()
{
    DeleteFontToHandle(fontHandle);
    DeleteFontToHandle(titleFontHandle);
    DeleteGraph(hBackGround);

}

// 定数
static const int MAX_STAGE = 3;

void StageSelectScene::Update()
{
    scrollX -= 2.0f; // 数字を大きくすると速くなります

    if (scrollX <= -bgWidth) {
        scrollX = 0;
    }
    if (KeyTrigger::CheckTrigger(KEY_INPUT_RIGHT)) {
        selectMap++;
        if (selectMap > 3)selectMap = 3;
    }

    if (KeyTrigger::CheckTrigger(KEY_INPUT_LEFT)) {
        selectMap--;
        if (selectMap < 1)selectMap = 1;
    }

    // 決定
    if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
        TitleScene::StopBGM();
        SceneManager::SetNextStage(selectMap);
        SceneManager::ChangeScene("PLAY");
    }
    
    if (CheckHitKey(KEY_INPUT_9))SceneManager::ChangeScene("GAMEOVER");
    if (CheckHitKey(KEY_INPUT_0))SceneManager::ChangeScene("GOAL");
    if (CheckHitKey(KEY_INPUT_O))SceneManager::ChangeScene("TITLE");

}

void StageSelectScene::Draw()
{
    if (hBackGround != -1) {
        // 1枚目
        DrawGraph((int)scrollX, 0, hBackGround, FALSE);

        // 2枚目（途切れないようにすぐ右隣に描画）
        DrawGraph((int)scrollX + bgWidth, 0, hBackGround, FALSE);
    }
    // Draw内で描画
    const char* titleText = "STAGE SELECT"; // 表示する文字
    int screenW = 1280; // 画面幅

    // 文字列の幅を取得
    int strWidth = GetDrawStringWidthToHandle(titleText, -1, titleFontHandle);

    // 真ん中のX座標を計算： (画面幅 - 文字幅) ÷ 2
    int titleX = (screenW - strWidth) / 2;

    // 計算した titleX を使って描画
    DrawStringToHandle(titleX, 50, titleText, GetColor(255, 255, 255),
        titleFontHandle);


    const char* mapName[MAX_STAGE] = {
        "EASY",
        "NORMAL",
        "HARD"
    };

    int boxW = 350;
    int boxH = 500;
    int y = 100;

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

    DrawStringToHandle(400, 620, "← → : 選択  SPACE : 決定", GetColor(200, 200, 200),titleFontHandle);
}

