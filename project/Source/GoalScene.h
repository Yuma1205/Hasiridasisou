#pragma once
#include "../Library/SceneBase.h"

class GoalScene : public SceneBase
{
private:
	int goal;

	int hImage;
	int bgImage;
	int gmImage;
	int glImage;

	int fadeAlpha;
	int fonthandle;
	int blinkTimer;
	int m_hBGM;
public:
	GoalScene();
	~GoalScene();
	

	void Update()override;
	void Draw()override;
};


