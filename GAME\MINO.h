#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <windows.h>
using namespace sf;
using namespace std;
// Model for tetramino:
// ---------
// | 0 | 1 |
// | 2 | 3 |
// | 4 | 5 |
// | 6 | 7 |
// ---------

std::vector<std::vector<int>> tetramino = { {0, 2, 4, 6}, {1, 3, 2, 4}, {0, 2, 3, 5}, {0, 1, 2, 3}, {0, 2, 4, 5}, {1, 3, 5, 4}, {0, 2, 4, 3} };
std::vector<std::vector<int>> pentamino = { {2, 4, 5, 6, 7} };

struct check {
	int x;
	int y;
};

class Mino {
public:

	Mino(std::vector<int>& A, int color) : size(A.size()), color(color) {
		mino.reserve(size);
		//Вверх
		for (int i = 0; i < size; ++i) {
			check tmp = { A[i] % (size - 2), A[i] / (size - 2) };
			mino.push_back(tmp);
		}
	}

	void rotate(bool rotate) {
		if (!rotate) return;
		check centre = mino[1];
		for (int i = 0; i < size; ++i) {
			int tmp = mino[i].x;
			mino[i].x = centre.y + centre.x - mino[i].y;
			mino[i].y = tmp + centre.y - centre.x;
		}
	}

	void move(int delta_x, int delta_y) {
		if (delta_x == 0 && delta_y == 0) return;
		for (int i = 0; i < size; ++i) {
			mino[i].x += delta_x;
			mino[i].y += delta_y;
		}
	}
	void setPosition(int x0, int y0) {
		for (int i = 0; i < size; ++i) { mino[i].x += x0; mino[i].y += y0; }
	}

	int getX(int i) { return mino[i].x; }
	int getY(int i) { return mino[i].y; }
	int getRealX(int i) { return mino[i].x * 40; }
	int getRealY(int i) { return mino[i].y * 40; }
	int getSize() { return size; }
	int getColor() { return color; }

private:
	int size;
	int color;
	std::vector<check> mino;
};
//*
class Game {
private:
	map<string, int> MinO;
public:
	int Pol, Schet;
	Game(int level) : ingame(tetramino[0], 0) , ingameFuture(tetramino[0], 0)
	{
		Pol = 1;
		Schet = 0;
		srand(time(0));
		MinO.emplace("First", rand() % 7);
		MinO.emplace("Second", rand() % 7);
		auto it = MinO.find("First");
		ingame = Mino(tetramino[it->second], it->second);
		ingame.setPosition(4, 0);
		it = MinO.find("Second");
		FutureMino(-1);
	}
	void ClearBackground()
	{
		for (int i = 10; i < 15; i++)
		{
			for (int j = 0 ; j < 7; j++)
			{
				background[i][j] = 0;
			}
		}
	}
	void ClearOLL()
	{
		auto it = MinO.find("Second");
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				background[i][j] = 0;
			}
		}
	}
	void FutureMino(int color)
	{
		if (color == -1)
		{
			ClearBackground();
			auto it = MinO.find("Second");
			ingameFuture = Mino(tetramino[it->second], it->second);
			ingameFuture.setPosition(12, 3);
			for (int i = 0; i < ingameFuture.getSize(); ++i)
			{
				background[ingameFuture.getX(i)][ingameFuture.getY(i)] = ingameFuture.getColor() + 1;
			}
		}
		else
		{
			if (Pol == 1)
			{
				ClearBackground();
				auto it = MinO.find("Second");
				ingameFuture = Mino(tetramino[it->second], it->second);
				ingameFuture.setPosition(12, 3);
				for (int i = 0; i < ingameFuture.getSize(); ++i)
				{
					background[ingameFuture.getX(i)][ingameFuture.getY(i)] = ingameFuture.getColor() + 1;
				}
				Mino Tmp1 = Mino(tetramino[color], color);
				ingameFuture = Mino(tetramino[color], color);
				ingameFuture.setPosition(12, 3);
			}
		}

	}
	void newMino(int color) {
		for (int i = 0; i < ingame.getSize(); ++i)
		{
			background[ingame.getX(i)][ingame.getY(i)] = ingame.getColor() + 1;
		}
		Mino tmp = Mino(tetramino[color], color);
		tmp.setPosition(4, 0);

		for (int i = 0; i < tmp.getSize(); ++i)
		{
			if (background[tmp.getX(i)][tmp.getY(i)])
			{
				Pol = 0;
			}
		}
		if (Pol == 1)
		{
			MinO["Second"] = rand() % 7;
			ingame = Mino(tetramino[color], color);
			ingame.setPosition(4, 0);
			FutureMino(MinO["Second"]);
		}
	}
	int borders(int delta_x = 0, int delta_y = 0, bool rotate = 0) {
		Mino tmp = ingame;

		if (delta_x != 0 || delta_y != 0) tmp.move(delta_x, delta_y);
		if (delta_y == 2) return borders(delta_x, delta_y - 1, 0);
		if (tmp.getColor() != 3)
		{
			tmp.rotate(rotate);
		}
		for (int i = 0; i < tmp.getSize(); ++i) {
			if (tmp.getY(i) == 0)
			{
				return 0;
			}
			if (tmp.getX(i) >= 10 || tmp.getX(i) < 0) return 0;
			if (delta_x != 0 && background[tmp.getX(i)][tmp.getY(i)]) return 0;
			if (tmp.getY(i) >= 20)
			{
				return 3;
			}
			if (background[tmp.getX(i)][tmp.getY(i)] && rotate == 1) {
				return 0;
			}
			if (background[tmp.getX(i)][tmp.getY(i)]) {
				return 3;
			}
		}
		ingame = tmp;
		return 1;
	}

	void tryRotate(bool& rotate) {
		if (!rotate) return;
		if (borders(0, 0, rotate) == 3) newMino(MinO["Second"]);
		rotate = 0;
	}

	void tryMove(int& delta_x, int& delta_y) {
		if (delta_x == 0 && delta_y == 0) return;
		if (borders(delta_x, delta_y, 0) == 3) newMino(MinO["Second"]);
		delta_x = 0, delta_y = 0;
	}

	void drawFigures(RenderWindow& w, Sprite& s) {
		for (int i = 0; i < 20; ++i)
			for (int j = 0; j < 20; ++j)
				if (background[i][j]) { s.setPosition(i * 40, j * 40); s.setTextureRect(IntRect((background[i][j] - 1) * 40, 0, 40, 40));  w.draw(s); }
		for (int i = 0; i < ingame.getSize(); ++i) {
			s.setPosition(ingame.getRealX(i), ingame.getRealY(i));
			s.setTextureRect(IntRect(ingame.getColor() * 40, 0, 40, 40));
			w.draw(s);
		}
	}

	void DelitSt()
	{
		int k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (background[j][i] != 0)
				{
					count++;
				}
				background[j][k] = background[j][i];
			}
			if (count < N) {
				k--;
			}
			else
			{
				Schet++;
				std::cout << Schet << '\n';
			}
		}
	}

private:
	int background[20][20] = { 0 };
	const int M = 20;
	const int N = 10;
	Mino ingame, ingameFuture;
};
