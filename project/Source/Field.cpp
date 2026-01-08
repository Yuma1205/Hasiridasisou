#include "Field.h"
#include <vector>
#include "Player.h"
#include "CsvReader.h"
#include "Greenslime.h"
#include "Redslime.h"

using namespace std;

const int ts = 64;
const int tf = 64 * 7;

vector<vector<int>> maps;

Field::Field(int stage)
{
	char filename[60];
	sprintf_s<60>(filename, "data/map%d.csv", stage);
	// CSVから読んで、mapsを作る
	CsvReader* csv = new CsvReader(filename);
	int lines = csv->GetLines(); // 縦の行数
	maps.resize(lines); // mapsの行数をcsvに合わせる
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y); // その行の横の数
		maps[y].resize(cols); // maps[y]の列数をcsvに合わせる
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			maps[y][x] = num;
		}
	}
	delete csv;

	hImage = LoadGraph("data/image/bgchar.png");

	bgImage = LoadGraph("data/image/BackGround.png");  // パスは必要に応じて変更
	GetGraphSize(bgImage, &bgWidth, nullptr);
	bgScrollX = 0;

	scrollX = 0;
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 2) {
				new Player(x * 64, y * 64);
			}
			if (maps[y][x] == 3) {
				new Greenslime(x * 64, y * 64);
			}
			if (maps[y][x] == 4) {
				new Redslime(x * 64, y * 64);
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
	Player* player = FindGameObject<Player>();

	if (player && !player->IsDead()) {
		scrollX += 5; //強制スクロールの場合
		bgScrollX += 5;    // 背景用スクロール
	}
	

	// 背景だけループさせる
	if (bgScrollX >= bgWidth) {
		bgScrollX -= bgWidth;
	}
}

void Field::Draw()
{
	DrawGraph(-bgScrollX, 0, bgImage, TRUE);
	DrawGraph(bgWidth - bgScrollX, 0, bgImage, TRUE);

	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 1) {
				DrawRectGraph(x * 64 - scrollX, y * 64, 0, 32, 64, 64, hImage, 1);
			}
		}
	}
}

bool Field::IsBlock(int px, int py)
{
	if (py >= maps.size())return false;
	if (px < 0 || px >= maps[py].size())return false;

	return maps[py][px] == 1;
}

int Field::HitCheckRight(int px, int py)
{
	if (py < 0)return 0;
	int x = px / 64;
	int y = py / 64;
	if (!IsBlock(x, y))return 0;
	return px % 64 + 1;
	
}

int Field::HitCheckLeft(int px, int py)
{
	if (py < 0)return 0;
	int x = px / 64;
	int y = py / 64;
	if (!IsBlock(x, y))return 0;
	return 64 - px % 64;
	
}

int Field::HitCheckUp(int px, int py)
{
	if (py < 0)return 0;
	int x = px / 64;
	int y = py / 64;
	if (!IsBlock(x, y))return 0;
	return 64 - py % 64;
	
}

int Field::HitCheckDown(int px, int py)
{
	if (py < 0)return 0;
	int x = px / 64;
	int y = py / 64;
	if (!IsBlock(x, y))return 0;
	return py % 64 + 1;
	
}

bool Field::OutOfMap(int px, int py)
{
	if (py > 64 * maps.size()) {
		return true;
	}
	return false;

}



