#include "Redslime.h"
#include "Field.h"
#include "Player.h"

static const float GRAVITY = 0.7f;

Redslime::Redslime(int sx, int sy)
{
    // 画像読み込み
    hImage = LoadGraph("data/image/Redslime2.png");

    // やられた音の読み込み
    hDeadSE = LoadSoundMem("data/Sound/se_enemy_dead04.mp3");
    ChangeVolumeSoundMem(255, hDeadSE);

    x = (float)sx;
    y = (float)sy;

    // 初期化
    vx = -3.0f; // 左へ進む
    vy = 0.0f;
    count = 0;
    pat = 0;
    onGround = false;
    isDead = false;
}

Redslime::~Redslime()
{
}

void Redslime::Update()
{
    // 死んでいたら処理しない
    if (isDead) return;

    Field* field = FindGameObject<Field>();
    if (field == nullptr) return;

    // --- 画面外判定 ---
    int scrollX = field->GetScrollX();
    float drawX = x - scrollX;
    if (drawX < -150 || drawX > 1280) return;

    if (drawX < -64) {
        isDead = true;
        return;
    }

    // --- プレイヤーとの当たり判定 ---
    Player* player = FindGameObject<Player>();

    if (player != nullptr && player->IsDead()) {
        return;
    }

    // プレイヤーが生きていれば判定を行う
    if (player != nullptr && !player->IsDead()) {

        // プレイヤーの判定領域
        float px = player->GetX() + 20;
        float py = player->GetY();
        float pw = 24;
        float ph = 60;

        // --- スライムの判定領域（円）に変更 ---
        // スライムの中心座標を計算（画像サイズ90x64の中心）
        float cx = x + 45.0f;
        float cy = y + 32.0f;
        // 半径（高さ64の半分は32ですが、少し小さくすると見た目と合います）
        float radius = 23.0f;

        // 1. プレイヤーの四角形の中で、スライムの中心に「一番近い点」を探す
        // （スライムの中心座標を、プレイヤーの四角形の範囲内に無理やり収める計算です）
        float nearX = max(px, min(cx, px + pw));
        float nearY = max(py, min(cy, py + ph));

        // 2. その「一番近い点」と「スライムの中心」との距離を計算する
        float distX = cx - nearX;
        float distY = cy - nearY;

        // 3. 距離の2乗が、半径の2乗より小さければ「当たっている」
        // （ルート計算を避けるため、2乗同士で比較するのが定石です）
        bool isHit = (distX * distX + distY * distY) < (radius * radius);

        if (isHit) {
            // 踏んだかどうかの判定
            float footY = py + ph;

            // 踏みつけ判定の高さ（ここはY座標ベースのままでOKですが、必要なら調整してください）
            // sy (つまり y) + 40 だったのでそのまま y + 40 で計算します
            if (player->GetVy() > 0 && footY < y + 40) {
                // 踏んだ！ -> スライム死亡、プレイヤー跳ねる
                isDead = true;
                player->Bounce();

                // やられた音を再生
                PlaySoundMem(hDeadSE, DX_PLAYTYPE_BACK);
            }
            else {
                // ぶつかった！ -> プレイヤー死亡
                player->Dead();
            }
        }
    }


    // --- 以下、移動と重力処理 ---
    x += vx;
    vy += GRAVITY;
    y += vy;

    // 床判定
    int push1 = field->HitCheckDown(x + 20, y + 64);
    int push2 = field->HitCheckDown(x + 70, y + 64);
    int push = max(push1, push2);

    if (push > 0) {
        y -= (push - 1);
        vy = 0;
        onGround = true;
    }
    else {
        onGround = false;
    }

    // アニメーション
    count++;
    if (count >= 15) {
        count = 0;
        pat++;
        if (pat >= 2) pat = 0;
    }
}

void Redslime::Draw()
{
    // 死んでいたら描画しない
    if (isDead) return;

    Field* field = FindGameObject<Field>();
    int scrollX = field ? field->GetScrollX() : 0;
    int scrollY = field ? field->GetScrollY() : 0;

    int drawX = (int)(x - scrollX);
    int drawY = (int)(y - scrollY);

    int srcX = pat * 90;
    DrawRectGraph(drawX, drawY, srcX, 0, 90, 64, hImage, TRUE, FALSE);
}