#pragma once
#include "ScreenBuffer.h"
#include <vector>
#include <iostream>
#include <windows.h>
#include <ctime>
#include "Field.h"
#include "Fruit.h"
#include "Snake.h"
#include "Game.h"
#include "CollisionManager.h"
#include "Menu.h"
#include "Score.h"
#include <thread>
class Game
{
public:
	Game() = default;
	void GameLoop();
	void KeyHandlingLoop();

	virtual ~Game() = default;

public:
	enum Command { CMD_NOCOMMAND = 0, CMD_EXIT, CMD_LEFT, CMD_RIGHT, CMD_UP, CMD_DOWN, CMD_ENTER };
	Command currentCommand = Command::CMD_NOCOMMAND;
	Coord delta = Coord({0, -1});
	bool stop = false;
};

