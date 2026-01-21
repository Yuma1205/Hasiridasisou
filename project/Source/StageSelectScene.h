#pragma once
#include "../Library/SceneBase.h"

class StageSelectScene : public SceneBase
{
private:
	int selectMap;
	int fontHandle;
	int titleFontHandle;

	int hBackGround; 
	int bgWidth;     
	float scrollX;   


	char keyOld[256];
public:
	StageSelectScene();
	~StageSelectScene();

	void Update()override;
	void Draw()override;
};

