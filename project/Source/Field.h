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
};

