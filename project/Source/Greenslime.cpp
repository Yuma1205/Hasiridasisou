#include "Greenslime.h"
#include "Field.h"
#include "Player.h" // ★Playerの情報を取得するために必要

static const float GRAVITY = 0.7f;

Greenslime::Greenslime(int sx, int sy)
{
    // 画像読み込み
    hImage = LoadGraph("data/image/Greenslime2.png");

    x = (float)sx;
    y = (float)sy;

    // 初期化
    vx = -1.0f; // 左へ進む
    vy = 0.0f;
    count = 0;
    pat = 0;
    onGround = false;
    isDead = false; // ★最初は生きている
}

Greenslime::~Greenslime()
{
}

void Greenslime::Update()
{
    // 死んでいたら処理しない
    if (isDead) return;

    Field* field = FindGameObject<Field>();
    if (field == nullptr) return;

    // --- 画面外判定 ---
    int scrollX = field->GetScrollX();
    float drawX = x - scrollX;
    // 画面外なら更新を止める(範囲は適宜調整)
    if (drawX < -150 || drawX > 1280) return;


    // --- プレイヤーとの当たり判定 ---
    Player* player = FindGameObject<Player>();

    // プレイヤーが生きていれば判定を行う
    if (player != nullptr && !player->IsDead()) {

        // プレイヤーの判定領域
        float px = player->GetX() + 20;
        float py = player->GetY();
        float pw = 24; // 幅(調整用)
        float ph = 60; // 高さ

        // スライムの判定領域（90x64）
        float sx = x;
        float sy = y;
        float sw = 90;
        float sh = 64;

        // 矩形の当たり判定
        bool isHit = (px < sx + sw && px + pw > sx && py < sy + sh && py + ph > sy);

        if (isHit) {
            // ★踏んだかどうかの判定
            // プレイヤーが落下中(vy > 0) かつ 足元がスライムの上半分にある時
            float footY = py + ph;
            // 踏みつけ判定の高さ(sy + 40)は遊び具合で調整
            if (player->GetVy() > 0 && footY < sy + 40) {
                // 踏んだ！ -> スライム死亡、プレイヤー跳ねる
                isDead = true;
                player->Bounce();
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

void Greenslime::Draw()
{
    // 死んでいたら描画しない
    if (isDead) return;

    Field* field = FindGameObject<Field>();
    int scrollX = field ? field->GetScrollX() : 0;

    int drawX = (int)(x - scrollX);
    int drawY = (int)y;

    int srcX = pat * 90;
    DrawRectGraph(drawX, drawY, srcX, 0, 90, 64, hImage, TRUE, FALSE);
}
