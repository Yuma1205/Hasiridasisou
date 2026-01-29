#pragma once
#include<iostream>
#include"../Library/GameObject.h"

class Goal : public GameObject
{
public:
	Goal(float sx,float sy);
	~Goal();
	void Update()override;
	void Draw()override;

	bool CheckHit(float px, float py, int pw, int ph);
	float GetX() const { return x; }
private:
	int hImage;
	float x, y;

	
};