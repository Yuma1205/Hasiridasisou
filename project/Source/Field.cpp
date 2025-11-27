#include "Field.h"
#include <vector>
#include "Player.h"
#include "CsvReader.h"

using namespace std;

const int ts = 64;
const int tf = 64 * 7;

//vector<vector<int>> maps = {
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//};

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

	scrollX = 0;
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 2) {
				new Player(x * 64, y * 64 );
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
	scrollX += 5; //強制スクロールの場合
	
}

void Field::Draw()
{
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 1) {
				DrawRectGraph(x * 64 - scrollX, y * 64, 0, 32, 64, 64, hImage, 1);
			}
		}
	}
}

int Field::HitCheckRight(int px, int py)
{
	if (py < 0)
		return 0;
	int x = px / 64;
	int y = (py - 400) / 64;
	if (maps[y][x] == 1)
		return px % 64 + 1;
	return 0;
}

int Field::HitCheckLeft(int px, int py)
{
	if (py < 0)
		return 0;
	int x = px / 64;
	int y = (py - 0) / 64;
	if (maps[y][x] == 1)
		return 64 - px % 64;
	return 0;
}

int Field::HitCheckUp(int px, int py)
{
	if (py < 0)
		return 0;
	int x = px / 64;
	int y = (py - 0) / 64;
	if (maps[y][x] == 1)
		return 64 - (py - 0) % 64;
	return 0;
}

int Field::HitCheckDown(int px, int py)
{
	if (py < 0) {
		return 0;
	}
	int x = px / 64;
	int y = (py - 0) / 64;
	if (maps[y][x] == 1)
		return (py - 0) % 64 + 1;
	return 0;
}

bool Field::OutOfMap(int px, int py)
{
	if (py > 0 + 64 * maps.size()) {
		return true;
	}
	return false;

}

int Field::GetScrollX() const { return scrollX; }
void Field::SetScrollX(int sx) { scrollX = sx; }

