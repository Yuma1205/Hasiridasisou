#include "StageSelectScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include <cstring>
#include "../Library/Trigger.h"


StageSelectScene::StageSelectScene()
{
	selectMap = 2;

	fontHandle = CreateFontToHandle("MS ゴシック", 64, -1, DX_FONTTYPE_ANTIALIASING);
	// コンストラクタで作成
	titleFontHandle = CreateFontToHandle("ＭＳ ゴシック", 32, -1, DX_FONTTYPE_ANTIALIASING);

	hBackGround = LoadGraph("data/image/TitleBackGround2.png");

	GetGraphSize(hBackGround, &bgWidth, NULL);

	scrollX = 0;

	// ★追加：各ステージのサムネイル画像を読み込み
	// ※画像ファイル名は実際の素材に合わせて変更してください
	// 推奨画像サイズ: 320x180 (16:9) または 640x360
	hStageGraph[0] = LoadGraph("data/image/stageEASY.png"); // EASY画像
	hStageGraph[1] = LoadGraph("data/image/stageNORMAL.png"); // NORMAL画像
	hStageGraph[2] = LoadGraph("data/image/stageHARD.png"); // HARD画像

	hSE = LoadSoundMem("data/sound/SelectSE.mp3");
}

StageSelectScene::~StageSelectScene()
{
	DeleteFontToHandle(fontHandle);
	DeleteFontToHandle(titleFontHandle);
	DeleteGraph(hBackGround);

	// ★追加：画像のメモリ解放
	for (int i = 0; i < 3; i++) {
		DeleteGraph(hStageGraph[i]);
	}

	DeleteSoundMem(hSE);
}

// 定数
static const int MAX_STAGE = 3;

void StageSelectScene::Update()
{
	scrollX -= 2.0f; // 数字を大きくすると速くなります

	if (scrollX <= -bgWidth) {
		scrollX = 0;
	}
	if (KeyTrigger::CheckTrigger(KEY_INPUT_RIGHT)) {
		PlaySoundMem(hSE, DX_PLAYTYPE_BACK);
		selectMap++;
		if (selectMap > 3)selectMap = 3;
	}

	// ★追加：左キー入力でSE再生
	if (KeyTrigger::CheckTrigger(KEY_INPUT_LEFT)) {
		PlaySoundMem(hSE, DX_PLAYTYPE_BACK);
		selectMap--;
		if (selectMap < 1)selectMap = 1;
	}

	// 決定
	if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
		PlaySoundMem(hSE, DX_PLAYTYPE_BACK);
		TitleScene::StopBGM();
		SceneManager::SetNextStage(selectMap);
		SceneManager::ChangeScene("PLAY");
	}

	if (CheckHitKey(KEY_INPUT_9))SceneManager::ChangeScene("GAMEOVER");
	if (CheckHitKey(KEY_INPUT_0))SceneManager::ChangeScene("GOAL");
	if (CheckHitKey(KEY_INPUT_O))SceneManager::ChangeScene("TITLE");

}

void StageSelectScene::Draw()
{
	// --- 背景描画 ---
	if (hBackGround != -1) {
		DrawGraph((int)scrollX, 0, hBackGround, FALSE);
		DrawGraph((int)scrollX + bgWidth, 0, hBackGround, FALSE);
	}

	// --- タイトル描画（影付き） ---
	const char* titleText = "STAGE SELECT";
	int screenW = 1280;
	int strWidth = GetDrawStringWidthToHandle(titleText, -1, fontHandle);
	int titleX = (screenW - strWidth) / 2;
	int titleY = 50; // ★変更：50 -> 70 (少し下へ)

	// 影と本体を描画 (fontHandleを使用)
	DrawStringToHandle(titleX + 4, 100 + 4, titleText, GetColor(0, 0, 0), fontHandle);
	DrawStringToHandle(titleX,100, titleText, GetColor(255, 255, 255), fontHandle);


	const char* mapName[MAX_STAGE] = { "EASY", "NORMAL", "HARD" };

	// 基本サイズ
	int baseBoxW = 380;
	int baseBoxH = 300;
	int centerY = 200 + baseBoxH / 2; // 箱の中心Y座標

	int margin = (screenW - baseBoxW * MAX_STAGE) / (MAX_STAGE + 1);

	for (int i = 0; i < MAX_STAGE; i++)
	{
		int mapNumber = i + 1;
		bool isSelect = (selectMap == mapNumber);

		// --- アニメーション計算 ---
		// 選択されていたらサイズを大きくする
		float scale = isSelect ? 1.1f : 1.0f;

		// 拡大縮小を考慮した幅と高さ
		int currentBoxW = (int)(baseBoxW * scale);
		int currentBoxH = (int)(baseBoxH * scale);

		// 中心基準で描画座標を計算
		int centerX = margin + i * (baseBoxW + margin) + baseBoxW / 2;

		int x1 = centerX - currentBoxW / 2;
		int y1 = centerY - currentBoxH / 2;
		int x2 = centerX + currentBoxW / 2;
		int y2 = centerY + currentBoxH / 2;

		// --- 半透明の箱を描画 ---
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200); // 200/255 の透明度
		DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを戻す

		// --- 枠線 ---
		if (isSelect) {
			// 選択中は枠線を太く
			DrawBox(x1 - 5, y1 - 5, x2 + 5, y2 + 5, GetColor(255, 255, 0), FALSE);
			DrawBox(x1 - 4, y1 - 4, x2 + 4, y2 + 4, GetColor(255, 255, 0), FALSE);
		}
		else {
			DrawBox(x1, y1, x2, y2, GetColor(0, 0, 0), FALSE);
		}

		// --- ★追加：サムネイル画像の描画 ---
		if (hStageGraph[i] != -1) // 画像が正しく読み込めていれば
		{
			// 画像の基本サイズ（アスペクト比 16:9 を想定）
			int imgBaseW = 350;
			int imgBaseH = 197;

			// 箱の拡縮に合わせて画像も拡縮
			int imgW = (int)(imgBaseW * scale);
			int imgH = (int)(imgBaseH * scale);

			// 表示位置（箱の中央、上寄り）
			int imgX = centerX - imgW / 2;
			int imgY = y1 + (int)(20 * scale); // 箱の上端から20px下

			// 画像を描画
			DrawExtendGraph(imgX, imgY, imgX + imgW, imgY + imgH, hStageGraph[i], TRUE);
		}

		// --- 文字（影付き＋中央寄せ） ---
		// 文字の位置を画像の下へ移動
		int strW = GetDrawStringWidthToHandle(mapName[i], -1, fontHandle);

		int textX = centerX - strW / 2;
		int textY = y1 + (int)(220 * scale); // 箱の上端から250px下（画像の下側）

		// 影
		DrawStringToHandle(textX + 3, textY + 3, mapName[i], GetColor(200, 200, 200), fontHandle);

		// 文字色（選択中は赤、通常は黒）
		unsigned int textColor = isSelect ? GetColor(255, 50, 50) : GetColor(50, 50, 50);
		DrawStringToHandle(textX, textY, mapName[i], textColor, fontHandle);
	}

	// --- 操作説明 ---
	DrawStringToHandle(400 + 2, 570 + 2, "← → : 選択  SPACE : 決定", GetColor(0, 0, 0), titleFontHandle); // 影
	DrawStringToHandle(400, 570, "← → : 選択  SPACE : 決定", GetColor(200, 200, 200), titleFontHandle);
}