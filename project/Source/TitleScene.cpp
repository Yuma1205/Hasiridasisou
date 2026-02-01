#include "TitleScene.h"
#include <DxLib.h>
#include "../Library/Trigger.h"

int TitleScene::m_hBGM = -1;

TitleScene::TitleScene()
{
	m_hBackGround = LoadGraph("data\\image\\TitleBackGround2.png");
	m_hPlayUI = LoadGraph("data\\image\\button.png");
	m_hChara = LoadGraph("data\\image\\Chara.png");
	m_hTitleLogo = LoadGraph("data\\image\\GameTitle2.png");

	// ★追加：SEの読み込み
	m_hSE = LoadSoundMem("data\\sound\\SelectSE.mp3");
	// 音量が大きければ調整してください (0-255)
	// ChangeVolumeSoundMem(128, m_hSE);

	direction = false;

	if (m_hBGM == -1) {
		m_hBGM = LoadSoundMem("data\\sound\\TitleBGM.mp3");
		ChangeVolumeSoundMem(128, m_hBGM);
	}
	if (m_hBGM != -1 && CheckSoundMem(m_hBGM) == 0) {
		PlaySoundMem(m_hBGM, DX_PLAYTYPE_LOOP);
	}

	count = 0;
	pat = 0;

	bgX = 0.0f;
	charaX = 200.0f;
	charaY = 540.0f;
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_hBackGround);
	DeleteGraph(m_hPlayUI);
	DeleteGraph(m_hChara);
	DeleteGraph(m_hTitleLogo);

	// ★追加：SEのメモリ削除
	DeleteSoundMem(m_hSE);
}

void TitleScene::StopBGM()
{
	if (m_hBGM != -1) {
		StopSoundMem(m_hBGM);   // 止める
		DeleteSoundMem(m_hBGM); // メモリから削除
		m_hBGM = -1;            // 状態を未読み込みに戻す
	}
}

void TitleScene::Update()
{
	// ★変更：SPACEキーでSEを再生してからシーン遷移
	if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
		PlaySoundMem(m_hSE, DX_PLAYTYPE_BACK);
		SceneManager::ChangeScene("STAGESELECT");
	}

	if (CheckHitKey(KEY_INPUT_P))     SceneManager::ChangeScene("STAGESELECT");
	if (CheckHitKey(KEY_INPUT_ESCAPE)) SceneManager::Exit();


	// --- アニメーション ---
	count++;
	if (count >= 8) {
		count = 0;
		pat++;
		if (pat >= 6) {
			pat = 0;
		}
	}

	// 背景スクロール
	bgX -= 2.0f;
	if (bgX <= -1280.0f) {
		bgX += 1280.0f;
	}
}

void TitleScene::Draw()
{
	DrawGraph((int)bgX, 0, m_hBackGround, FALSE);
	DrawGraph((int)bgX + 1280, 0, m_hBackGround, FALSE);

	int frameW = 64;
	int frameH = 64;
	int srcX = pat * frameW;
	int srcY = 192;

	DrawRectGraph((int)charaX, (int)charaY, srcX, srcY, frameW, frameH, m_hChara, TRUE, !direction);

	if (m_hTitleLogo != -1) {
		int targetW = 850;
		int targetH = 400;
		int x = (1280 - targetW) / 2;
		int y = 30;
		DrawExtendGraph(x, y, x + targetW, y + targetH, m_hTitleLogo, TRUE);
	}

	if (m_hPlayUI != -1) {
		int targetW = 630;
		int targetH = 400;
		int x = (1280 - targetW) / 2;
		int y = 245;
		DrawExtendGraph(x, y, x + targetW, y + targetH, m_hPlayUI, TRUE);
	}
}