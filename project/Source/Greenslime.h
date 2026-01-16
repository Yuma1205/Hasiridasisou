#pragma once
#include "../Library/GameObject.h"

class Greenslime : public GameObject
{
public:
    Greenslime(int x, int y);
    ~Greenslime();
    void Update() override;
    void Draw() override;

private:
    int hImage;
    float x, y;

    // 移動・アニメーション用
    float vx;
    int count;
    int pat;

    // ★追加：重力・判定用
    float vy;      // 縦の速度
    bool onGround; // 地面に足がついているか
    bool isDead;
    int hDeadSE;
};

