#include "Player.h"
#include "Field.h"
#include"../Library/Trigger.h"
#include"GameOver.h"
#include<assert.h>


static const float Gravity = 0.7;
static const float JUMP_POWER = -10.0f;
static const float GROUND_Y = 600;

const int FRAME_W = 64;
const int FRAME_H = 64;

enum State {
    STATE_IDLE,
    STATE_ATTACK
};

State state = STATE_IDLE;

int count = 0;
int pat = 0;

const int IDLE_FRAMES = 6;
const int ATTACK_FRAMES = 2;

Player::Player()
{
    hImage = LoadGraph("data/image/Chara.png");
    x = 200.0f;
    y = 500.0f;
    vy = 0.0f;

    jumpCount = 0;
    MaxjumpCount = 1;

    onGround = false;
    isDead = false;
    direction = false;
}

Player::Player(int sx, int sy)
{
    hImage = LoadGraph("data/image/Chara.png");
    x = (float)sx;
    y = (float)sy;
    vy = 0.0f;

    jumpCount = 0;
    MaxjumpCount = 1;

    onGround = false;
    isDead = false;
    direction = false;
}

Player::~Player()
{
}

void Player::Update()
{
    if (isDead) return;
    x += 5;  // 強制スクロールに追従

    if (onGround && jumpCount < MaxjumpCount) {
        jumpCount += 1;
    }

    Field* field = FindGameObject<Field>();
    int scrollX = field->GetScrollX();


    // 横移動（スクロール）の前に壁チェック
    int Right1 = field->HitCheckRight(x + 50, y + 5);
    int Right2 = field->HitCheckRight(x + 50, y + 63);
    int pushRight = max(Right1, Right2);

    int Left1 = field->HitCheckLeft(x + 14, y + 5);
    int Left2 = field->HitCheckLeft(x + 14, y + 63);
    int pushLeft = max(Left1, Left2);

    // 地上のみ壁に当たったら押し戻す
    if (onGround) {
        x -= pushRight;
        x += pushLeft;
    }

    // --- ジャンプ ---
    if (onGround) {
        if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
            vy = JUMP_POWER;
            onGround = false;
        }
    }

    //---二段ジャンプ---
    if (!onGround && jumpCount == MaxjumpCount)
    {
        if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE))
        {
            jumpCount -= 1;
            vy = JUMP_POWER;
        }
    }


    y += vy;

    // 上下の重力処理
    if (vy < 0) {
        vy += Gravity * 0.6f; // 上昇はゆっくり
    }
    else {
        vy += Gravity * 1.2f; // 下降は速く
    }

    // --- 地面との衝突 ---
    if (vy >= 0) {
        int push1 = field->HitCheckDown(x + 14, y + 64);
        int push2 = field->HitCheckDown(x + 50, y + 64);
        int push = max(push1, push2);
        if (push > 0) {
            y -= push - 1;
            vy = 0;
            onGround = true;
        }
        else {
            onGround = false;
            if (field->OutOfMap(x, y)) {
                new GameOver();
            }
        }
    }
    else {
        // 頭上との衝突
        int push1 = field->HitCheckUp(x + 14, y + 5);
        int push2 = field->HitCheckUp(x + 50, y + 5);
        int push = max(push1, push2);
        if (push > 0) {
            y += push;
            vy = 0;
        }
    }



    if (state == STATE_ATTACK) {
        count++;
        if (count >= 4) {
            count = 0;
            pat++;
            if (pat >= ATTACK_FRAMES) {
                pat = 0;
                state = STATE_IDLE;
            }
        }
        return;
    }

    if (CheckHitKey(KEY_INPUT_E)) {
        state = STATE_ATTACK;
        count = 0;
        pat = 0;
        return;
    }

    count++;
    if (count >= 10) {
        count = 0;
        pat++;
        if (pat >= IDLE_FRAMES)pat = 0;
    }

}

void Player::Draw()
{
    Field* field = FindGameObject<Field>();
    int scrollX = field->GetScrollX();
    int drawX = (int)(x - field->GetScrollX());
    int drawY = (int)y;

    int srcX = 0, srcY = 0;

    if (state == STATE_ATTACK) {
        const int FRAME_X = 2;
        const int FRAME_Y = 2;
        const int TOTAL_FRAME = FRAME_X * FRAME_Y;

        int index = pat % TOTAL_FRAME;
        srcX = (4 + (index % FRAME_X)) * FRAME_W;
        srcY = (index / FRAME_X) * FRAME_H;
    }
    else {
        const int FRAME_X = 2;//横
        const int FRAME_Y = 3;//縦
        const int TOTAL_FRAME = FRAME_X * FRAME_Y;


        int index = pat % TOTAL_FRAME;
        srcX = ((index % FRAME_X) + 2) * FRAME_W;
        srcY = ((index / FRAME_X) + 3) * FRAME_H;
    }


    DrawRectGraph(drawX, drawY, srcX, srcY, FRAME_W, FRAME_H, hImage, TRUE, !direction);

}
