#pragma once
#include "../Library/GameObject.h"

class Redslime : public GameObject
{
public:
    Redslime(int x, int y);
    ~Redslime();
    void Update() override;
    void Draw() override;

private:
    int hImage;
    float x, y;

    // 移動・アニメーション用
    float vx;
    int count;
    int pat;

    // 重力・判定用
    float vy;
    bool onGround;

    // 倒されたかどうかのフラグ
    bool isDead;
    int hDeadSE;
};

