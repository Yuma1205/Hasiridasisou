#pragma once
#include "../Library/SceneBase.h"

class GoalScene : public SceneBase
{
private:
	int goal;
public:
	GoalScene();
	~GoalScene();
	

	void Update()override;
	void Draw()override;
};


