#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Common.h"

PlayScene::PlayScene()
{
    gameState = STATE_READY;
    stateTimer = 0;
    new Field(1);

}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
    switch (gameState)
    {
    case STATE_READY:
        stateTimer++;
        if (stateTimer > 90) {   // 1秒
            gameState = STATE_GO;
            stateTimer = 0;
            return;
        }
        return;    //ゲーム更新を止める

    case STATE_GO:
        stateTimer++;
        if (stateTimer > 30) {   // 0.5秒
            gameState = STATE_PLAY;
        }
        return;    //ゲーム更新を止める

    case STATE_PLAY:
        //ここに来て初めて通常ゲームが動く
        break;
    }
    if (CheckHitKey(KEY_INPUT_T)) {
        SceneManager::ChangeScene("TITLE");
    }
}

void PlayScene::Draw()
{
    // READY
    if (gameState == STATE_READY) {
        DrawString(600, 300, "Ready", GetColor(255, 255, 255));
    }
    // GO
    else if (gameState == STATE_GO) {
        DrawString(600, 300, "Go!", GetColor(255, 255, 0));
    }
    // 通常ゲームの描画
    if (gameState == STATE_PLAY) {
        // ボールやブロックの描画
    }
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
    DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
