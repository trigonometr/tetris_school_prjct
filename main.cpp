#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <GAME\MINO.h>
using namespace sf;
using namespace std;
int main(int argc, char** argv)
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	RenderWindow window(VideoMode(640, 800), "Tetris");

	Texture checks;

	checks.loadFromFile("checks.png");
	Sprite check(checks, IntRect(0, 0, 40, 40));
		
	Texture OVER;
	OVER.loadFromFile("TEST.png");
	Sprite SPRITE(OVER);

	Texture NewMinoFon;
	NewMinoFon.loadFromFile("Lab.png");
	Sprite NMF(NewMinoFon);

	Texture RESTART;
	RESTART.loadFromFile("RES.png");
	Sprite RES(RESTART);

	Texture background;
	background.loadFromFile("background.png");
	Sprite sprite(background);

	int delta_x = 0, delta_y = 0;
	bool rotation = 0;
	float dtime = 0, pause = 1, game_time = -20;

	int i = 1;

	Game tetris(0);

	Clock time;
	time.restart();
	while (window.isOpen())
	{
		dtime += time.getElapsedTime().asSeconds();
		time.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Up) { rotation = 1; }
				else if (event.key.code == Keyboard::Left) { delta_x = -1; }
				else if (event.key.code == Keyboard::Right) { delta_x = 1; }
				else if (event.key.code == Keyboard::Down) { delta_y = 1; }
			if (tetris.Pol == 0 && event.key.code == Keyboard::Enter)
			{
				game_time = -20;
				pause = 1;
				dtime = 0;
				tetris.Pol = 1;
				tetris.ClearOLL();
			}
		}

		if (dtime > pause) { ++delta_y; game_time += pause;  dtime = 0; }
		tetris.DelitSt();
		tetris.tryMove(delta_x, delta_y);
		tetris.tryRotate(rotation);

		if (game_time > 20 * i) { pause /= 1.5; ++i; }

		window.clear();
		window.draw(NMF);
		window.draw(sprite);
		tetris.drawFigures(window, check);		
		if (tetris.Pol == 0)
		{
			window.draw(SPRITE);
			window.draw(RES);
		}
		window.display();
	}

	return 0;
}
