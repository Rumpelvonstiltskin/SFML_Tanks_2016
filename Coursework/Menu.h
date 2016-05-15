/*
===========================================================================
This project distributed under GNU GPLv3
Copyright (C) 2015 Chabanenko Dmitry
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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gamedef.h"


class Menu
{
public:
	sf::Sound musicTheme;
	si musicVolumeState = 1;
	si sfxVolumeState = 9;
public:
	Menu();
	~Menu();

	void update(float deltaTime, si gameState);
	void draw(sf::RenderWindow& window);
	si GetPressedItem();
private:
	sf::Font about;
	sf::Font menuItems;
	sf::Text item[6];
	sf::Text aboutItem[3];
	sf::RectangleShape bar[10][2];
	sf::SoundBuffer menuThemeBuffer;

	si selectedItemIndexMenu;
	si selectedItemIndexOptions;
	si gameState = MENU;	// MENU

	float delayTime = 0;
};

