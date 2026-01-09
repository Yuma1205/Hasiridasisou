#include "Togetoge.h"
#include "Field.h"
#include "Player.h"

// アニメーション設定
const int FRAME_W = 64;
const int FRAME_H = 64;
const int ANIM_WAIT = 10;
const int ANIM_FRAMES = 4;

Togetoge::Togetoge(float sx, float sy)
{
    hImage = LoadGraph("data/image/Togetoge.png");
    x = sx;
    y = sy;
    vy = 0.0f; // 初期速度は0

    count = 0;
    pat = 0;
}

Togetoge::~Togetoge()
{
}

void Togetoge::Update()
{
    // --- プレイヤー情報の取得 ---
    Player* player = FindGameObject<Player>();
    // プレイヤーが死んでいるかどうかのフラグ
    bool isPlayerDead = (player != nullptr && player->IsDead());


    // --- アニメーション処理 ---
    // ★修正：プレイヤーが生きてる時だけアニメーションを進める
    if (!isPlayerDead) {
        count++;
        if (count >= ANIM_WAIT) {
            count = 0;
            pat++;
            if (pat >= ANIM_FRAMES) {
                pat = 0;
            }
        }
    }


    // --- 重力処理と地面との衝突判定 ---
    Field* field = FindGameObject<Field>();

    // 重力を加算 (GRAVITYはヘッダーで定義済み)
    vy += GRAVITY;
    y += vy;

    // 地面判定
    // 画像サイズは64ですが、少し足元をめり込ませるために +60 で判定
    int push1 = field->HitCheckDown(x + 14, y + 54);
    int push2 = field->HitCheckDown(x + 50, y + 54);
    int push = max(push1, push2);

    if (push > 0) {
        // 地面にめり込んだ分だけ押し戻す
        y -= (push - 1);
        vy = 0; // 着地
    }
    else {
        if (field->OutOfMap(x, y)) {
            // 何もしない
        }
    }

    if (!isPlayerDead) {

        float px = player->GetX() + 14;
        float py = player->GetY() + 5;
        float pw = 36;
        float ph = 59;

        // トゲトゲの判定領域
        float ex = x + HIT_OFFSET_X;
        float ey = y + HIT_OFFSET_Y;
        float ew = HIT_WIDTH;
        float eh = HIT_HEIGHT;

        if (px < ex + ew &&
            px + pw > ex &&
            py < ey + eh &&
            py + ph > ey)
        {
            // 当たったらプレイヤー死亡
            player->Dead();
        }
    }
}

void Togetoge::Draw()
{
    Field* field = FindGameObject<Field>();

    // 横スクロール位置
    int scrollX = field ? field->GetScrollX() : 0;

    // 縦スクロール位置（Fieldに追加したGetScrollYを使用）
    // ※もしFieldにGetScrollYがない場合は、エラーになるので int scrollY = 0; に戻してください
    int scrollY = field ? field->GetScrollY() : 0;

    int drawX = (int)(x - scrollX);
    int drawY = (int)(y - scrollY); // ★Y座標もスクロールさせる

    int srcX = pat * FRAME_W;
    int srcY = 0;

    DrawRectGraph(drawX, drawY, srcX, srcY, FRAME_W, FRAME_H, hImage, TRUE);
}