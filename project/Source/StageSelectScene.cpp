#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"
#include <cstring>
#include "../Library/Trigger.h"


StageSelectScene::StageSelectScene()
{
    selectMap = 2;

    fontHandle = CreateFontToHandle("MS ƒSƒVƒbƒN", 64, -1, DX_FONTTYPE_ANTIALIASING);
    // ƒRƒ“ƒXƒgƒ‰ƒNƒ^‚Åì¬
    titleFontHandle = CreateFontToHandle("‚l‚r ƒSƒVƒbƒN", 32, -1, DX_FONTTYPE_ANTIALIASING);
}

StageSelectScene::~StageSelectScene()
{
    DeleteFontToHandle(fontHandle);
    DeleteFontToHandle(titleFontHandle);

}

// ’è”
static const int MAX_STAGE = 3;

void StageSelectScene::Update()
{
    if (KeyTrigger::CheckTrigger(KEY_INPUT_RIGHT)) {
        selectMap++;
        if (selectMap > 3)selectMap = 3;
    }

    if (KeyTrigger::CheckTrigger(KEY_INPUT_LEFT)) {
        selectMap--;
        if (selectMap < 1)selectMap = 1;
    }

    // Œˆ’è
    if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
        SceneManager::SetNextStage(selectMap);
        SceneManager::ChangeScene("PLAY");
    }
    
    if (CheckHitKey(KEY_INPUT_9))SceneManager::ChangeScene("GAMEOVER");
    if (CheckHitKey(KEY_INPUT_0))SceneManager::ChangeScene("GOAL");
    if (CheckHitKey(KEY_INPUT_O))SceneManager::ChangeScene("TITLE");

}

void StageSelectScene::Draw()
{
    // Draw“à‚Å•`‰æ
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

        // ”wŒiƒ{ƒbƒNƒX
        DrawBox(x, y, x + boxW, y + boxH, GetColor(255, 255, 255), TRUE);

        // ˜gü
        int borderThikness = isSelect ? 6 : 2;
        for (int t = 0; t < borderThikness; t++) {
            DrawBox(
                x - t, y - t,
                x + boxW + t, y + boxH + t,
                isSelect ? GetColor(255, 255, 0) : GetColor(0, 0, 0),
                FALSE
            );
        }

        // •¶Žš’†‰›Šñ‚¹
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

    DrawStringToHandle(180, 620, "© ¨ : ‘I‘ð  SPACE : Œˆ’è", GetColor(200, 200, 200),titleFontHandle);
}

