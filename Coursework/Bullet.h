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
#include "gamedef.h"

class Bullet
{
public:
	bool life = true;
	bool hit = false;
public:
	Bullet(sf::Texture& texture, sf::Vector2f gunPos, float gunAngle, float level);
	~Bullet();

	void update(float deltaTime, sf::Vector2f tankEnemyPos); 
	void draw(sf::RenderWindow& window);
	
	sf::Vector2f getPosition();
private:
	sf::Texture bulletTexture;
	sf::Sprite muzzleFlash;
	sf::Sprite bullet;
	sf::Vector2f gunPos;

	float delayTime;
	float dx;
	float dy;
	float gunAngle;
};

