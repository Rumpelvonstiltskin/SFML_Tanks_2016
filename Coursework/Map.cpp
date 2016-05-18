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

#include "Map.h"


Map::Map(sf::Texture &texture)
{
	map.setTexture(texture);
	map.setTextureRect(sf::IntRect(0, 1080, 1920, 840));

	for (int i = 0; i <= 2; ++i) {
		lines[i].setSize(sf::Vector2f(5, 150));
		lines[i].setFillColor(sf::Color(44, 228, 255));
		lines[i].setPosition(875 + i * 80, -150 + pow(-1, i) * i * 50);
	}
}


void Map::draw(sf::RenderWindow& window)
{
	window.draw(map);

	for (int i = 0; i <= 2; ++i)
		window.draw(lines[i]);
}


void Map::update(float deltaTime)
{
	for (int i = 0; i <= 2; ++i)
		lines[i].move(0, 0.5 * deltaTime);

	if (lines[1].getPosition().y > 1080)
		for (int i = 0; i <= 2; ++i)
			lines[i].setPosition(875 + i * 80, -150 + pow(-1, i) * i * 50);
}


Map::~Map()
{
}
