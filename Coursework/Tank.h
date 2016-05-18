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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "Bullet.h"
#include "gamedef.h"


class Tank
{
public:
	Tank(sf::Texture& texture);
	~Tank();
	sf::Vector2f getTankPosition();
	sf::Vector2f getFirstBulletPosition();

	virtual void update(float deltaTime, sf::Vector2f botPos, bool enemyHit, si sfxVolumeState, sf::Vector2f mousePos);
	void draw(sf::RenderWindow& window);
	float getGunRotation();
public:
	struct stats {
		si healingPoints;
		si armor;
		si gold;
		si msLevel;
		si asLevel;
		si bsLevel;
		bool upgradeAvailability = false;
		stats(si healingPoints, si armor, si gold, si msLevel, si asLevel, si bsLevel, bool upgradeAvailability)
		{
			this->healingPoints = healingPoints;
			this->armor = armor;
			this->gold = gold;
			this->msLevel = msLevel;
			this->asLevel = asLevel;
			this->bsLevel = bsLevel;
			this->upgradeAvailability = upgradeAvailability;
		}
	} stats;


	bool life = true;
	si drawPriority;
	bool enemyHit;
protected:
	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator it;

	sf::Sprite tankBody;
	sf::Sprite tankGun;
	sf::SoundBuffer shotBuf;
	sf::Sound shot;
	sf::Mouse mouse;
	sf::Texture bulletTexture;
	sf::Sprite explosion;
	sf::SoundBuffer upgradeBuf;
	sf::Sound sUpgrade;

	float rotationSpeed;
	float movementSpeed;

	float bulletDelayTime;
	float shotSoundDelayTime;
	float deltaTime;
	float hitDelayTime;
	float respawnTime;

	float secondCounterOne;
	float secondCounterTwo;

	bool rotate;
protected:
	void explode(sf::Vector2f hitPos);
	virtual void kill();
};
