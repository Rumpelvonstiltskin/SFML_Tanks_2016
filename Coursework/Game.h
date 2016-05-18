/*
===========================================================================
This project distributed under GNU GPLv3
Copyright (C) 2016 Chabanenko Dmitry
This file is part of the Tanks GPL Source Code.
Tanks Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Tanks Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Tanks Source Code.  If not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#pragma once

#pragma comment(lib, "C:\\SFML-2.3.2\\lib\\sfml-graphics")
#pragma comment(lib, "C:\\SFML-2.3.2\\lib\\sfml-system")
#pragma comment(lib, "C:\\SFML-2.3.2\\lib\\sfml-window")
#pragma comment(lib, "C:\\SFML-2.3.2\\lib\\sfml-audio")

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Tank.h"
#include "Bullet.h"
#include "Map.h"
#include "GameInterface.h"
#include "MouseCursor.h"
#include "TankBot.h"
#include "gamedef.h"

extern int width, height;

class Game {
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow window;
	sf::Texture gameTexture;

	Menu* menu;
	Map* map;
	Tank* player;
	MouseCursor* dynamicCursor;
	TankBot* bot;
	GameInterface* gameInterface;
	sf::SoundBuffer levelThemeBuffer;
	sf::Sound musicTheme;
	sf::Mouse mouse;

	si gameState;
private:
	void update(float deltaTime);
	void render();
	void processEvents();
};