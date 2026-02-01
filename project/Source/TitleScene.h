#pragma once
#include "../Library/SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;

	static void StopBGM();

private:
	int m_hBackGround;
	int m_hPlayUI;
	int m_hChara;
	int m_hTitleLogo;

	// ★追加：SE用ハンドル
	int m_hSE;

	bool direction;

	static int m_hBGM;

	int count;
	int pat;

	float bgX;

	float charaX;
	float charaY;
};