#pragma once
#include "../Library/SceneBase.h"
#include "DxLib.h"     

class ReadyGoManager : public SceneBase
{
private:
    int timer;
    int state; // 0:Ready, 1:Go, 2:Finished

    bool started;

    int hReady;
    int hGo;

    int hSeReady;
    int hSeGo;

    const int TIME_READY = 60; // 2秒
    const int TIME_GO = 45;     // 1秒

public:
    ReadyGoManager() {
        timer = 0;
        state = 0;

        started = false;

        hReady = LoadGraph("data/image/Ready.png");
        hGo = LoadGraph("data/image/Go.png");

        hSeReady = LoadSoundMem("data/sound/se_Ready.mp3");
        hSeGo = LoadSoundMem("data/sound/se_Go.mp3");

    }

    ~ReadyGoManager() {
        DeleteGraph(hReady);
        DeleteGraph(hGo);

        DeleteSoundMem(hSeReady);
        DeleteSoundMem(hSeGo);
    }

    void Start() {
        if (!started) {
            started = true;
            PlaySoundMem(hSeReady, DX_PLAYTYPE_BACK);
        }
    }

    bool IsStarted() { return started; }

    void Update() {
        if (!started) return;
        if (state == 2) return;

        timer++;
        if (state == 0) {
            if (timer >= TIME_READY) {
                state = 1;
                timer = 0;

                PlaySoundMem(hSeGo, DX_PLAYTYPE_BACK);
            }
        }
        else if (state == 1) {
            if (timer >= TIME_GO) state = 2;
        }
    }

    void Draw() {
        if (!started) return;
        if (state == 2) return;

        int screenW, screenH;
        GetDrawScreenSize(&screenW, &screenH);

        int imgW, imgH;
        int currentHandle = 0;

        if (state == 0) currentHandle = hReady;
        else if (state == 1) currentHandle = hGo;

        GetGraphSize(currentHandle, &imgW, &imgH);

        int drawX = (screenW - imgW) / 2;
        int drawY = 150;

        DrawGraph(drawX, drawY, currentHandle, TRUE);
    }

    bool IsActive() { return (state != 2); }
};

class PlayScene : public SceneBase
{
private:
    ReadyGoManager* m_readyGo;
    int stageNo;

    // 残機システム用
    static int lives;      // シーンが変わっても値を保持するためにstaticにする
    int hLifeImage;        // 表示用画像

    int hBGM;

    // リスタート待機処理用
    bool isSceneChanging;  // 死んでから画面が変わるまでの待機フラグ
    int restartTimer;      // 待機時間を数えるタイマー
    int fadeAlpha;
    unsigned int fadeColor;

public:
    PlayScene();
    ~PlayScene();
    void Update() override;
    void Draw() override;

    // リセット用関数（リスタート時に使う）
    void Reset();
};