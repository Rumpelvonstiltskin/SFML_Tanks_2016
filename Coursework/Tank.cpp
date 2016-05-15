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

#include "Tank.h"


Tank::Tank(sf::Texture& texture) : 
	drawPriority(1), 
	rotationSpeed(0.2), 
	bulletDelayTime(0), 
	shotSoundDelayTime(0),
	hitDelayTime(100),
	respawnTime(3000),
	secondCounterOne(0),
	secondCounterTwo(0),
	rotate(false)
{
	si r, g, b;

	r = 20 + static_cast<int> (rand() % 100);
	g = 20 + static_cast<int> (rand() % 100);
	b = 20 + static_cast<int> (rand() % 100);

	tankBody.setTexture(texture);
	tankBody.setTextureRect(sf::IntRect(0, 1925, 145, 205));
	tankBody.setColor(sf::Color(r, g, b));
	tankBody.setOrigin(72.5, 137.65);
	tankBody.setPosition(500, 500);

	tankGun.setTexture(texture);
	tankGun.setTextureRect(sf::IntRect(145, 1925, 145, 205));
	tankGun.setColor(sf::Color(r, g, b));
	tankGun.setOrigin(72.5, 134.5);
	tankGun.setPosition(500, 500);

	explosion.setTexture(texture);
	explosion.setTextureRect(sf::IntRect(469, 1925, 200, 200));
	explosion.setOrigin(100, 100);

	bulletTexture = texture;

	shotBuf.loadFromFile("Resources//shot.ogg");
	shot.setBuffer(shotBuf);

	upgradeBuf.loadFromFile("Resources//upgrade_1.ogg");
	sUpgrade.setBuffer(upgradeBuf);
}


void Tank::draw(sf::RenderWindow& window)
{
	hitDelayTime -= deltaTime;
	if (hitDelayTime > 0) {
		window.draw(explosion);
		drawPriority = 0;
	}
	else {
		drawPriority = 1;
	}

	window.draw(tankBody);
	window.draw(tankGun);

	for (it = bullets.begin(); it != bullets.end(); it++){
		(*it)->draw(window);
	}
}


void Tank::update(float deltaTime, sf::Vector2f botPos, bool enemyHit, si sfxVolumeState, sf::Vector2f mousePos)
{
	sf::Vector2f tankPos = tankBody.getPosition();
	float tankBodyAngle = tankBody.getRotation();

	this->deltaTime = deltaTime;
	this->enemyHit = enemyHit;

	if (enemyHit) {
		if (stats.armor) {
			stats.armor -= TANK_DAMAGE;
		}
		else {
			stats.healingPoints -= TANK_DAMAGE;
		}
	}

	this->enemyHit = false;

	// shot
	bulletDelayTime += deltaTime;
	shotSoundDelayTime += deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (bulletDelayTime >= 1000 - 100 * stats.asLevel) {
			if (BATTLE_ZONE) {
				bullets.push_back(new Bullet(bulletTexture, tankGun.getPosition(), tankGun.getRotation(), stats.bsLevel));
				if (shotSoundDelayTime > 100 && life == true) {
					shot.setVolume(sfxVolumeState * 10);
					shot.play();
					shotSoundDelayTime = 0;
				}
			}
			bulletDelayTime = 0;
		}
	}

	for (it = bullets.begin(); it != bullets.end();) {
		Bullet *b = *it;
		if (b->hit) {
			stats.gold += 20;
			explode(b->getPosition());
			hitDelayTime = 100;
			this->enemyHit = true;
		}

		if (b->life == false) {
			it = bullets.erase(it);
			delete b;
		}
		else it++;
	}

	for (it = bullets.begin(); it != bullets.end(); it++) {
		(*it)->update(deltaTime, botPos);
	}


	if (stats.healingPoints <= 0) {
		life = false;
		kill();
		return;
	}

	life = true;

	// gun rotation
	sf::Vector2f gunPos = tankGun.getPosition();

	float dx = mouse.getPosition().x - gunPos.x;
	float dy = mouse.getPosition().y - gunPos.y;

	float angle = atan2(dy, dx) * 180 / PI + 90;

	if (dy < 0 && dx < 0) {		// have no idea why
		angle += 360;
	}

	if (abs(tankBodyAngle - angle) < 30 || abs(tankBodyAngle - angle) > 330) {
		tankGun.setRotation(angle);
	}

	// upgrade
	secondCounterOne += deltaTime;
	secondCounterTwo += deltaTime;

	if (secondCounterOne >= SECOND) {
		stats.gold++;
		secondCounterOne = 0;
	}

	if (UPGRADE_AREA) {
		stats.upgradeAvailability = true;
	}
	else {
		stats.upgradeAvailability = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stats.upgradeAvailability == true) {
		if (secondCounterTwo > UPGRADE_DELAY_TIME) {
			sUpgrade.play();

			if (mousePos.y > 1035 && mousePos.y < 1075 && stats.gold >= 100) {
				if (mousePos.x > 430 && mousePos.x < 470) {
						stats.gold -= 100;
						stats.msLevel += 1;
						secondCounterTwo = 0;
				}

				if (mousePos.x > 730 && mousePos.x < 770) {
					stats.gold -= 100;
					stats.asLevel += 1;
					secondCounterTwo = 0;
				}

				if (mousePos.x > 1030 && mousePos.x < 1070) {
					stats.gold -= 100;
					stats.bsLevel += 1;
					secondCounterTwo = 0;
				}

				if (mousePos.x > 1330 && mousePos.x < 1370) {
					stats.gold -= 100;
					stats.armor += 100;
					secondCounterTwo = 0;
				}
			}
		}
	}

	// move
	movementSpeed = 0.3 + 0.1 * stats.msLevel;
	tankBodyAngle = tankBodyAngle * PI / 180;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		tankBody.rotate(-rotationSpeed * deltaTime);
		tankGun.rotate(-rotationSpeed * deltaTime);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		tankBody.rotate(rotationSpeed * deltaTime);
		tankGun.rotate(rotationSpeed * deltaTime);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		tankBody.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		tankBody.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	// collision
	if (tankPos.x > LEFT_SHORE_X) {
		tankBody.setPosition(LEFT_SHORE_X, tankPos.y);
		tankGun.setPosition(LEFT_SHORE_X, tankPos.y);
	}

	if (tankPos.x < LEFT_BORDER_X) {
		tankBody.setPosition(LEFT_BORDER_X, tankPos.y);
		tankGun.setPosition(LEFT_BORDER_X, tankPos.y);
	}

	if (tankPos.y < HIGHER_BORDER_Y) {
		tankBody.setPosition(tankPos.x, HIGHER_BORDER_Y + 0.1);
		tankGun.setPosition(tankPos.x, HIGHER_BORDER_Y + 0.1);
	}

	if (tankPos.y > LOWER_BORDER_Y) {
		tankBody.setPosition(tankPos.x, LOWER_BORDER_Y);
		tankGun.setPosition(tankPos.x, LOWER_BORDER_Y);
	}

}


void Tank::explode(sf::Vector2f hitPos)
{
	explosion.setPosition(hitPos);
}


sf::Vector2f Tank::getTankPosition()
{
	sf::Vector2f pos = tankBody.getPosition();
	return pos;
}


float Tank::getGunRotation()
{
	return tankGun.getRotation();
}


void Tank::kill()
{
	if (respawnTime > 0) {
		tankBody.setPosition(-300, -300);
		tankGun.setPosition(-300, -300);
		tankBody.setRotation(0);
		tankGun.setRotation(0);
		respawnTime -= deltaTime;
	}
	else {
		tankBody.setPosition(500, 500);
		tankGun.setPosition(500, 500);
		stats.healingPoints = 100;
		respawnTime = 3000;
	}
}


sf::Vector2f Tank::getFirstBulletPosition()
{
	sf::Vector2f pos = { 0, 0 };
	if (bullets.size() > 0) {
		return bullets.front()->getPosition();
	}
	else {
		return pos;
	}
}


Tank::~Tank()
{
}