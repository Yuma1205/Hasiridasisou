#pragma once
#include "../Library/GameObject.h"

class Common : public GameObject
{
public:
	Common();
	void Draw() override;

	int stageNumber;
	int score;
	int hiScore;
};

