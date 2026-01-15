#pragma once
#include "../Library/SceneBase.h"

class GoalScene : public SceneBase
{
private:
	int goal;

	int hImage;
	int bgImage;

	int fadeAlpha;
public:
	GoalScene();
	~GoalScene();
	

	void Update()override;
	void Draw()override;
};


