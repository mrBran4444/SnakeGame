#include "Game.h"
#include <conio.h>

void Game::GameLoop()
{
	srand(time(0));
	const size_t width = 120;
	const size_t height = 30;
	while (!stop)
	{
		ScreenBuffer screen(width, height);
		{
			Menu menu;
			screen.AddDrawable(&menu);
			menu.SetAbsolutePosition({ width / 2,height / 2 });
			screen.Draw();
			while (true)
			{
				if (currentCommand == Game::Command::CMD_ENTER)
				{
					if (menu.GetChoice() == Choice::Quit)
					{
						stop = true;
						return;
					}
					screen.RemoveDrawable(&menu);
					break;
				}
				else if (currentCommand != Game::Command::CMD_NOCOMMAND)
				{
					menu.Next();
					screen.Draw();
				}
				Sleep(100);
			}
		}

		{
			const size_t fieldWidth = width;
			const size_t fieldHeight = height - 3;
			const size_t fruitWidth = fieldWidth - 2;
			const size_t fruitHeight = fieldHeight - 3;
			Field field(fieldWidth, fieldHeight);
			Fruit fruit(fruitWidth, fruitHeight);
			Snake snake({ width / 2, height / 2 });
			CollisionManager collisionManager;
			Score score;
			score.SetAbsolutePosition({ width / 2, fieldHeight + 1 });

			field.BindCollisionCallback(&snake, [&snake]() {
				snake.Die();
			});
			fruit.BindCollisionCallback(&snake, [&score, &snake, &fruit]() {
				snake.Grow(fruit.GetSymbol());
				fruit.NextPosition();
				score.AddPoint();
			});
			snake.BindCollisionCallback(&snake, [&snake]() {
				snake.Die();
			});


			std::vector< CPICollisionable> snakeCollapsable;
			snakeCollapsable.push_back(&field);
			snakeCollapsable.push_back(&snake);
			snakeCollapsable.push_back(&fruit);
			collisionManager.AddCollisionGroup({ &snake, snakeCollapsable });

			fruit.SetAbsolutePosition({ 1,1 });
			screen.AddDrawable(&field);
			screen.AddDrawable(&fruit);
			screen.AddDrawable(&snake);
			screen.AddDrawable(&score);
			while (!snake.Dead())
			{
				screen.Draw();
				snake.SetDirection(delta);
				snake.Move();
				collisionManager.ProcessCollisions();
				Sleep(100);
			}
		}
	}
}

void Game::KeyHandlingLoop()
{
	while (!stop)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			currentCommand = Command::CMD_RIGHT;
			delta = Coord(1, 0);
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			currentCommand = Command::CMD_LEFT;
			delta = Coord(-1, 0);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			currentCommand = Command::CMD_UP;
			delta = Coord(0, -1);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			currentCommand = Command::CMD_DOWN;
			delta = Coord(0, 1);
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			currentCommand = Command::CMD_ENTER;
		}
		else
		{
			currentCommand = Command::CMD_NOCOMMAND;
		}
	}
}