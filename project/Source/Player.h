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
    void UpdateDead();
    void UpdateAttack();
    void UpdateIdle();
    
    bool IsDead() const;

private:
    int hImage;
    float x, y;
    float vy;

    
        enum State {
            STATE_IDLE,
            STATE_ATTACK,
            STATE_DEAD
        };

        State state;
        int count;
        int pat;
        bool gameOverCalled;


    bool onGround;
    bool isDead;
    bool direction;
    int  currentFrame;

    int jumpCount;
    int MaxjumpCount;


};