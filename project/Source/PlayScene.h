#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
enum GameStartState {
	STATE_READY,
	STATE_GO,
	STATE_PLAY,
};
class PlayScene : public SceneBase
{
private:
	GameStartState gameState;
	int stateTimer;
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
};
