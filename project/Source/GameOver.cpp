#include "GameOver.h"
#include<assert.h>
#include"Player.h"

GameOver::GameOver()
{
	
}

GameOver::~GameOver()
{
}

void GameOver::Update()
{
		SceneManager::ChangeScene("GAMEOVER");
}

void GameOver::Draw()
{
	
}
