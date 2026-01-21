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

	bool direction;

	static int m_hBGM;

	int count;
	int pat;

	// ★変更：背景のスクロール用変数
	float bgX;

	// キャラクターの表示位置（画面上のどこに固定するか）
	float charaX;
	float charaY;
};