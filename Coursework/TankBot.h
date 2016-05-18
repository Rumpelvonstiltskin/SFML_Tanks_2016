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
#include "Tank.h"
#include <SFML/Graphics.hpp>
#include "gamedef.h"

class TankBot : public Tank
{
public:
	TankBot(sf::Texture& texture);
	~TankBot();
	void update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPos, bool playerLife, bool enemyHit, si sfxVolumeState);
	struct switchers {
		bool moveForward = false;
		bool moveBackward = false;
		bool rotateRight = false;
		bool rotateLeft = false;
		bool shoot = false;
	} switcher;
private:
	enum decisions {
		FORWARD_MOVEMENT = 1, BACKWARD_MOVEMENT, ROTATION_LEFT, ROTATION_RIGHT, SHOT
	};
	
	float time;
	float decisionTime;
	si decision;
	si upgrade;
private:
	void kill() override;
};

