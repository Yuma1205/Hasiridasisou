#pragma once
#include "../Library/SceneBase.h"

class StageSelectScene : public SceneBase
{
private:
	int selectMap;
public:
	StageSelectScene();
	~StageSelectScene();

	void Update()override;
	void Draw()override;
};

