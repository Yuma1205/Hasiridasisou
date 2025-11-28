#include "Trigger.h"
#include<DxLib.h>
#include<sstream>

namespace KeyBuffer
{
    static const float REPEAT_TIME = 0.5f;

    static bool tiggerKeyBufferArray[0xff];
}

void KeyTrigger::Init()
{
    for (int i=0;i < 0xff;i++)
    {
        KeyBuffer::tiggerKeyBufferArray[i] = false;
    }
}

bool KeyTrigger::CheckTrigger(int keyCode)
{
    bool TriggerFlag = false;

    if (CheckHitKey(keyCode) != 0)
    {
        if (!KeyBuffer::tiggerKeyBufferArray[keyCode])
        {
            TriggerFlag = true;
        }
        KeyBuffer::tiggerKeyBufferArray[keyCode] = true;
    }
    else
    {
        KeyBuffer::tiggerKeyBufferArray[keyCode] = false;
    }
    return TriggerFlag;
}
