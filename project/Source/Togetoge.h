#pragma once
#include "../Library/GameObject.h"

class Togetoge : public GameObject
{
public:
    Togetoge(float x, float y);
    ~Togetoge();
    void Update() override;
    void Draw() override;

private:
    int hImage;
    float x, y;
    float vy; // 落下速度

    // アニメーション用
    int count;
    int pat;

    // 重力
    const float GRAVITY = 0.5f;

    // 当たり判定のサイズ調整用
    const int HIT_OFFSET_X = 10;
    const int HIT_OFFSET_Y = 20;
    const int HIT_WIDTH = 44;
    const int HIT_HEIGHT = 44;
};

