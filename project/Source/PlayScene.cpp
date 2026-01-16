#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Common.h"
#include "../Library/SceneManager.h"
#include "../Library/ObjectManager.h"
#include "GameOver.h"

int PlayScene::lives = 0;

PlayScene::PlayScene()
{
    m_readyGo = new ReadyGoManager();
    int stage = SceneManager::GetNextStage();
    new Field(stage);

    isSceneChanging = false;
    restartTimer = 0;

    // ★最初は「白」からフェードイン
    fadeAlpha = 255;
    fadeColor = GetColor(255, 255, 255);

    if (lives <= 0) {
        lives = 3;
    }

    hLifeImage = LoadGraph("data/image/Chara.png");
    hBGM = LoadSoundMem("data/Sound/stageBGM.mp3");
    ChangeVolumeSoundMem(160, hBGM);

}

PlayScene::~PlayScene()
{
    if (m_readyGo) {
        delete m_readyGo;
        m_readyGo = nullptr;
    }

    DeleteGraph(hLifeImage);

    StopSoundMem(hBGM);
    DeleteSoundMem(hBGM);

    ObjectManager::DeleteAll();
}

void PlayScene::Reset()
{
    ObjectManager::DeleteAll();

    isSceneChanging = false;
    restartTimer = 0;

    // ★リスタート時は「白」にセット
    fadeAlpha = 255;
    fadeColor = GetColor(255, 255, 255);

    int stage = SceneManager::GetNextStage();
    new Field(stage);

    StopSoundMem(hBGM);

    if (m_readyGo) {
        delete m_readyGo;
    }
    m_readyGo = new ReadyGoManager();

    StopSoundMem(hBGM);
}

void PlayScene::Update()
{

    if (!isSceneChanging && fadeAlpha > 0) {
        fadeAlpha -= 5;
        if (fadeAlpha < 0) {
            fadeAlpha = 0;
        }
    }

    if (fadeAlpha == 0 && !m_readyGo->IsStarted()) {
        m_readyGo->Start();
    }

    // ReadyGo演出の更新
    m_readyGo->Update();
    if (m_readyGo->IsActive()) {
        return;
    }
    if (!isSceneChanging && CheckSoundMem(hBGM) == 0 && lives > 0) {
        PlaySoundMem(hBGM, DX_PLAYTYPE_LOOP);
    }
    if (isSceneChanging) {
        restartTimer++;

        // 画面を暗くする（リスタート演出）
        fadeAlpha = 255 * restartTimer / 120;
        if (fadeAlpha > 255) { fadeAlpha = 255; }

        // 2秒経ったらリセット
        if (restartTimer == 120) {
            lives--; // 残機を減らす
            Reset(); // リスタート
        }

        return; 
    }

    // 通常のゲーム更新
    ObjectManager::Update();

    // プレイヤーの死亡チェック
    Player* player = FindGameObject<Player>();
    if (player != nullptr) {
        if (player->IsDead() && player->IsAnimEnd() && lives > 0) {

            if (lives == 1) {
                lives--;        // 0にする
                new GameOver(); // すぐに文字を表示

                StopSoundMem(hBGM);
            }
            else {

                isSceneChanging = true;
                restartTimer = 0;

                // フェードアウトの色を「黒」にセット
                fadeColor = GetColor(0, 0, 0);

                StopSoundMem(hBGM);
            }
        }
    }

    // デバッグ用
    if (CheckHitKey(KEY_INPUT_O)) {
        lives = 0;
        SceneManager::ChangeScene("TITLE");
    }
}

void PlayScene::Draw()
{
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

    ObjectManager::Draw();
    m_readyGo->Draw();

    // 残機アイコンの描画
    for (int i = 0; i < lives; i++) {
        int srcX = 128;
        int srcY = 192;
        int drawX = 20 + (i * 50);
        int drawY = 20;

        DrawRectRotaGraph(
            drawX + 24, drawY + 24, srcX, srcY, 64, 64, 0.75, 0.0,
            hLifeImage, TRUE, TRUE
        );
    }

    // ★フェード描画
    if (fadeAlpha > 0) {
        int w, h;
        GetDrawScreenSize(&w, &h);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);

        // 指定された色（白または黒）で塗りつぶす
        DrawBox(0, 0, w, h, fadeColor, TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}