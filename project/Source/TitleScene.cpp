#include "TitleScene.h"
#include <DxLib.h>
#include "../Library/Trigger.h"

TitleScene::TitleScene()
{
	m_hBackGround = LoadGraph("data\\image\\TitleBackGround2.png");
	m_hPlayUI = LoadGraph("data\\image\\button.png");
	m_hChara = LoadGraph("data\\image\\Chara.png");
	m_hTitleLogo = LoadGraph("data\\image\\GameTitle2.png");

	direction = false;

	count = 0;
	pat = 0;

	// ★変更：背景のスタート位置は0
	bgX = 0.0f;

	// ★変更：キャラクターは「画面の少し左寄り(200)」に固定します
	// これで「カメラがキャラを捉え続けている」ように見えます
	charaX = 200.0f;
	charaY = 540.0f;
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_hBackGround);
	DeleteGraph(m_hPlayUI);
	DeleteGraph(m_hChara);
	DeleteGraph(m_hTitleLogo);
}

void TitleScene::Update()
{

	if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) SceneManager::ChangeScene("STAGESELECT");
	if (CheckHitKey(KEY_INPUT_P))     SceneManager::ChangeScene("STAGESELECT");
	if (CheckHitKey(KEY_INPUT_ESCAPE)) SceneManager::Exit();


	// --- アニメーション (走る動き) ---
	count++;
	// アニメーション速度調整 (数字を小さくすると足の回転が速くなります)
	if (count >= 8) {
		count = 0;
		pat++;
		if (pat >= 6) {
			pat = 0;
		}
	}

	// ★メイン処理：背景を左へ流す (速度2)
	bgX -= 2.0f;

	// 背景画像が1枚分(1280px)左に行ききったら、元の位置(0)に戻してループさせる
	// ※画像の横幅が1280ではない場合、ここの数字を画像の横幅に合わせてください
	if (bgX <= -1280.0f) {
		bgX += 1280.0f; // ズレを補正するために += 1280.0f の方が滑らかですが、まずはこれで
	}
}

void TitleScene::Draw()
{
	// 1. 背景を描画 (無限ループ処理)
	// ---------------------------------------------------
	// 1枚目：現在の bgX の位置に描く
	DrawGraph((int)bgX, 0, m_hBackGround, FALSE);

	// 2枚目：1枚目の「すぐ右隣 (+1280)」に描く
	// これで1枚目が左に見切れても、右から新しい背景が入ってきます
	DrawGraph((int)bgX + 1280, 0, m_hBackGround, FALSE);
	// ---------------------------------------------------


	// 2. キャラクター
	// 画面上の位置(charaX = 200)は動かさず、足のアニメーションだけ再生します
	int frameW = 64;
	int frameH = 64;
	int srcX = pat * frameW;
	int srcY = 192;

	DrawRectGraph((int)charaX, (int)charaY, srcX, srcY, frameW, frameH, m_hChara, TRUE, !direction);


	// 3. タイトルロゴ
	if (m_hTitleLogo != -1) {
		int targetW = 850;
		int targetH = 400;
		int x = (1280 - targetW) / 2;
		int y = 30;
		DrawExtendGraph(x, y, x + targetW, y + targetH, m_hTitleLogo, TRUE);
	}

	// 4. Play SPACE ボタン
	if (m_hPlayUI != -1) {
		int targetW = 630;
		int targetH = 400;
		int x = (1280 - targetW) / 2;
		int y = 225;
		DrawExtendGraph(x, y, x + targetW, y + targetH, m_hPlayUI, TRUE);
	}

	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255, 255, 255));
}