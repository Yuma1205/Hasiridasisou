#include "Goal.h"
#include "Field.h"
#include<assert.h>

Goal::Goal(float sx, float sy)
{
    hImage = LoadGraph("data/image/Goalobj.png");
    assert(hImage != -1);

    x = sx;
    y = sy;
}


Goal::~Goal()
{
}

void Goal::Update()
{

}

void Goal::Draw()
{
    Field* field = FindGameObject<Field>();
    int scrollX = field ? field->GetScrollX() : 0;
    int scrollY = field ? field->GetScrollY() : 0;

    int drawX = (int)(x - scrollX);
    int drawY = (int)(y - scrollY);


    DrawRectRotaGraph(drawX, drawY,0,0,1536,1024,0.2f,0.0, hImage, TRUE);
}

bool Goal::CheckHit(float px, float py, int pw, int ph)
{
    // ゴールのサイズ（描画に合わせる）
    int gw = int(1536 * 0.2f);
    int gh = int(1024 * 0.2f);

    // 矩形同士の当たり判定
    if (px < x + gw &&
        px + pw > x &&
        py < y + gh &&
        py + ph > y)
    {
        return true;
    }

    return false;
}
