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

    
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetVy() const { return vy; }

    // 追加：敵との接触時のアクション
    void Bounce();  
    void Dead();    

    bool IsAnimEnd() const { return smokeEnd; }

private:
    int hImage;
    float x, y;
    float vy;
    int hJumpSE;
    int hSeDead;


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

    // --- 煙アニメ用 ---
    int hSmoke;
    int smokeCount;
    int smokePat;
    bool smokeEnd;

    float deadDrawX;
    float deadDrawY;

};