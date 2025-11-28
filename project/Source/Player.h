#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
    Player();
    Player(int sx, int sy);
    ~Player();
    void Update() override;
    void Draw() override;
    bool IsDead() const { return isDead; }

private:
    int hImage;
    float x, y;
    float vy;
    bool onGround;
    bool isDead;
    bool direction;
    int  currentFrame;

    int jumpCount;
    int MaxjumpCount;


};