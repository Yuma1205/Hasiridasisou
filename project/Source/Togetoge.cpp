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
    isDead = false; // ヘッダーに合わせて初期化
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

    // ★修正：関数の最初で Field を取得する（これで下のエラーが消えます）
    Field* field = FindGameObject<Field>();

    // フィールド情報を使って座標計算
    int scrollX = 0;
    if (field != nullptr) {
        scrollX = field->GetScrollX();
    }

    float drawX = x - scrollX;

    // 画面外（左側）に消えたら処理しない
    if (drawX < -64) {
        isDead = true;
        return;
    }

    // --- アニメーション処理 ---
    // プレイヤーが生きてる時だけアニメーションを進める
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

    // 重力を加算 (GRAVITYはヘッダーで定義済み)
    vy += GRAVITY;
    y += vy;

    // 地面判定
    // 画像サイズは64ですが、少し足元をめり込ませるために +60 (または54) で判定
    if (field != nullptr) {
        int push1 = field->HitCheckDown((int)(x + 14), (int)(y + 54));
        int push2 = field->HitCheckDown((int)(x + 50), (int)(y + 54));
        int push = max(push1, push2);

        if (push > 0) {
            // 地面にめり込んだ分だけ押し戻す
            y -= (push - 1);
            vy = 0; // 着地
        }
        else {
            if (field->OutOfMap((int)x, (int)y)) {
                // 何もしない（落下死させるならここに記述）
            }
        }
    }

    // --- プレイヤーとの当たり判定 ---
    if (!isPlayerDead && player != nullptr) {

        float px = player->GetX() + 14;
        float py = player->GetY() + 5;
        float pw = 36;
        float ph = 59;

        // トゲトゲの判定領域
        float ex = x + HIT_OFFSET_X;
        float ey = y + HIT_OFFSET_Y;
        float ew = (float)HIT_WIDTH;
        float eh = (float)HIT_HEIGHT;

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

    // 縦スクロール位置
    // Field.h に GetScrollY がない場合は 0 に固定します
    int scrollY = 0;

    int drawX = (int)(x - scrollX);
    int drawY = (int)(y - scrollY);

    int srcX = pat * FRAME_W;
    int srcY = 0;

    DrawRectGraph(drawX, drawY, srcX, srcY, FRAME_W, FRAME_H, hImage, TRUE);
}