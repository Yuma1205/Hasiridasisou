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

const int IDLE_FRAMES = 6;
const int ATTACK_FRAMES = 2;
const int DEAD_FRAMES = 4;



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

    state = STATE_IDLE;
    count = 0;
    pat = 0;
    gameOverCalled = false;

    hSmoke = LoadGraph("data/image/smoke.png");

    smokeCount = 0;
    smokePat = 0;
    smokeEnd = false;

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

    state = STATE_IDLE;
    count = 0;
    pat = 0;
    gameOverCalled = false;

    hSmoke = LoadGraph("data/image/smoke.png");

    smokeCount = 0;
    smokePat = 0;
    smokeEnd = false;

}

Player::~Player()
{
}

void Player::Update()
{
    switch (state)
    {
    case STATE_DEAD:
        UpdateDead();
        return;

    case STATE_ATTACK:
        UpdateAttack();
        break;

    case STATE_IDLE:
    default:
        UpdateIdle();
        break;
    }

    if (onGround && jumpCount < MaxjumpCount) {
        jumpCount += 1;
    }

    Field* field = FindGameObject<Field>();
    int scrollX = field->GetScrollX();


    // 横移動（スクロール）の前に壁チェック
    float nextX = x + 5;

    int Right1 = field->HitCheckRight(nextX + 50, y + 5);
    int Right2 = field->HitCheckRight(nextX + 50, y + 63);

    if (Right1 > 0 || Right2 > 0) {
        //壁にめり込む前で止める
        x = (int)(nextX / 64) * 64 - 50;

        state = STATE_DEAD;
        isDead = true;

        deadDrawX = x - field->GetScrollX();
        deadDrawY = y;

        count = 0;
        pat = 0;

        // 煙初期化
        smokeCount = 0;
        smokePat = 0;
        smokeEnd = false;

        return;

    }

    x = nextX;

    int Left1 = field->HitCheckLeft(x + 14, y + 5);
    int Left2 = field->HitCheckLeft(x + 14, y + 63);
    int pushLeft = max(Left1, Left2);

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
                state = STATE_DEAD;
                isDead = true;

                deadDrawX = x - field->GetScrollX();
                deadDrawY = y;

                count = 0;
                pat = 0;

                // 煙初期化
                smokeCount = 0;
                smokePat = 0;
                smokeEnd = false;

                return;

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
        if (y < 0) {
            y = 0;
            vy = 0;
        }
    }

    if (CheckHitKey(KEY_INPUT_E) && state != STATE_ATTACK) {
        state = STATE_ATTACK;
        count = 0;
        pat = 0;
    }

    
}

void Player::Draw()
{
    Field* field = FindGameObject<Field>();
    int scrollX = field->GetScrollX();
    int scrollY = field->GetScrollY();
    int drawX;
    int drawY;

    if (state == STATE_DEAD) {
        deadDrawX = x;
        deadDrawY = y;
        drawX = (int)(deadDrawX - field->GetScrollX());
        drawY = (int)deadDrawY;
    }

    else {
        drawX = (int)(x - field->GetScrollX());
        drawY = (int)(y - scrollY);
    }


    int srcX = 0, srcY = 0;

    switch (state) {
    case STATE_DEAD:
    {
        srcX = 6 * FRAME_W;
        srcY = 5 * FRAME_H;
        break;


    }
    case STATE_ATTACK:
    {
        const int FRAME_X = 2;
        const int FRAME_Y = 2;
        const int TOTAL_FRAME = FRAME_X * FRAME_Y;

        int index = pat % TOTAL_FRAME;
        srcX = (4 + (index % FRAME_X)) * FRAME_W;
        srcY = (index / FRAME_X) * FRAME_H;
        break;
    }

    case STATE_IDLE:
    default:
    {
        const int FRAME_X = 2;//横に何枚使うか
        const int FRAME_Y = 3;//縦に何枚使うか
        const int TOTAL_FRAME = FRAME_X * FRAME_Y;//全部で何枚のフレームか


        int index = pat % TOTAL_FRAME;
        srcX = ((index % FRAME_X) + 2) * FRAME_W;//どこのフレームから使うか（横）
        srcY = ((index / FRAME_X) + 3) * FRAME_H;//どこのフレームから使うか（縦）
        break;
    }
    }

    DrawRectGraph(drawX, drawY, srcX, srcY, FRAME_W, FRAME_H, hImage, TRUE, !direction);

    // --- 煙描画 ---
    if (state == STATE_DEAD && !smokeEnd) {
        const int SMOKE_W = 64;
        const int SMOKE_H = 64;

        int smokeX = smokePat * SMOKE_W;
        int smokeY = 0;

        DrawExtendGraph(
            drawX,
            drawY,
            drawX + 64,
            drawY + 64,
            hSmoke,
            TRUE
        );
    }
}

bool Player::IsDead() const
{
    return isDead;
}

void Player::Bounce()
{
    vy = -10.0f; // 跳ねる強さ
    onGround = false;
    jumpCount = 1;
}

void Player::Dead()
{
    if (state != STATE_DEAD) {
        state = STATE_DEAD;
        isDead = true;
        count = 0;
        pat = 0;
    }
}

void Player::UpdateDead()
{
    if (smokeEnd) {
        if (!gameOverCalled) {
            new GameOver();
            gameOverCalled = true;
        }
        return;
    }

    smokeCount++;
    if (smokeCount >= 6) { // 煙の速さ
        smokeCount = 0;
        smokePat++;

        if (smokePat >= 6) { // 煙のコマ数（画像に合わせる）
            smokeEnd = true;
        }
    }

    
}


void Player::UpdateAttack()
{

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

void Player::UpdateIdle()
{
    count++;
    if (count >= 10) {
        count = 0;
        pat++;
        if (pat >= IDLE_FRAMES)pat = 0;
    }
}
