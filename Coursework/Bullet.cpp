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

#include "Bullet.h"


Bullet::Bullet(sf::Texture& texture, sf::Vector2f gunPos, float gunAngle, float level) : 
	delayTime(25), 
	dx(35), 
	dy(35)
{
	bullet.setTexture(texture);
	bulletTexture.setSmooth(true);
	bullet.setTextureRect(sf::IntRect(435, 1925, 34, 34));
	bullet.setOrigin(17, 17);

	muzzleFlash.setTexture(texture);
	muzzleFlash.setTextureRect(sf::IntRect(469, 1925, 200, 200));
	muzzleFlash.setOrigin(100, 100);
	muzzleFlash.setScale(0.5, 0.5);

	gunAngle = gunAngle * PI / 180;
	bullet.setPosition(gunPos.x + GUN_LENGTH * sin(gunAngle), gunPos.y - GUN_LENGTH * cos(gunAngle));

	dx = (0.5 + level / 5) * sin(gunAngle);
	dy = -(0.5 + level / 5) * cos(gunAngle);

	this->gunPos = gunPos;
	this->gunAngle = gunAngle;
}


Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime, sf::Vector2f tankEnemyPos)
{
	sf::Vector2f bulletPos = bullet.getPosition();

	if (bulletPos.x < tankEnemyPos.x + 70 && bulletPos.x > tankEnemyPos.x - 70 && 
		bulletPos.y > tankEnemyPos.y - 65 && bulletPos.y < tankEnemyPos.y + 65) {
		hit = true;
		life = false;
	}

	muzzleFlash.setPosition(gunPos.x + GUN_LENGTH * sin(gunAngle), gunPos.y - GUN_LENGTH * cos(gunAngle));
	bullet.move(dx * deltaTime, dy * deltaTime);
	delayTime -= deltaTime;

	if (OUTSIDE_AREA) life = false;
}

sf::Vector2f Bullet::getPosition()
{
	return bullet.getPosition();
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(bullet);
	if (delayTime > 0) {
		window.draw(muzzleFlash);
	}
}
