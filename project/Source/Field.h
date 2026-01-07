#pragma once
#include "../Library/GameObject.h"
#include <vector>

class Player;

class Field : public GameObject
{
public:
    Field(int stage);
    ~Field();
    void Update() override;
    void Draw() override;
    int GetScrollX() const;
    void SetScrollX(int sx);
    int HitCheckRight(int px, int py);
    int HitCheckLeft(int px, int py);
    int HitCheckUp(int px, int py);
    int HitCheckDown(int px, int py);
    bool OutOfMap(int px, int py);
private:
    int hImage;
    int scrollX;
    std::vector<Player*> players;
    bool IsBlock(int px, int py);
   

    //――――――――――――――――――――――――
    // ★ 背景ループ用変数（追加）
    //――――――――――――――――――――――――
    int bgImage;     // 背景画像
    int bgWidth;     // 背景画像の横幅
    int bgScrollX;   // 背景専用スクロール位置
};

