#pragma once
#include<iostream>
#include"../Library/GameObject.h"

class GameOver : public GameObject
{
public:
	GameOver();
	~GameOver();
	void Update()override;
	void Draw()override;
private:
	int hImage;
	int gameOverTimer;
};
