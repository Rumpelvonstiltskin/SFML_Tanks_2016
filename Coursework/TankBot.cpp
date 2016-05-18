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

#include "TankBot.h"


TankBot::TankBot(sf::Texture& texture) : Tank(texture), time(0), decisionTime(0)
{
	tankBody.setPosition(1420, 500);
	tankGun.setPosition(1420, 500);

	drawPriority = 0;
}


void TankBot::update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPos, bool playerLife, bool enemyHit, si sfxVolumeState)
{
	this->deltaTime = deltaTime;
	sf::Vector2f tankPos = tankBody.getPosition();
	float tankBodyAngle = tankBody.getRotation();

	this->enemyHit = enemyHit;
	if (enemyHit) {
		if (stats.armor) {
			stats.armor -= 20;
		}
		else {
			stats.healingPoints -= 20;
		}
	}
	this->enemyHit = false;

	bulletDelayTime += deltaTime;
	shotSoundDelayTime += deltaTime;

	if (switcher.shoot) {
		if (bulletDelayTime >= 1000 - 100 * stats.asLevel) {
			bullets.push_back(new Bullet(bulletTexture, tankPos, tankGun.getRotation(), stats.bsLevel));
			bulletDelayTime = 0;

			if (shotSoundDelayTime > 100) {
				shot.setVolume(sfxVolumeState * 10);
				shot.play();
				shotSoundDelayTime = 0;
			}
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
		(*it)->update(deltaTime, playerPos);
	}

	if (stats.healingPoints <= 0) {
		life = false;
		kill();
		return;
	}

	//bot decisions
	if (stats.gold >= 100) {
		stats.gold -= 100;
		
		if (sUpgrade.getStatus() == 0) {
			sUpgrade.setVolume(sfxVolumeState * 10);
			sUpgrade.play();
		}

		upgrade = 1 + static_cast<si>(rand() % 3);

		switch (upgrade) {
			case 1:
				stats.msLevel++;
				break;
			case 2:
				stats.asLevel++;
				break;
			case 3:
				stats.bsLevel++;
				break;
			case 4:
				stats.armor++;
				break;
			default:
				break;
		}
	}

	float angle = atan2(tankPos.y - playerPos.y, tankPos.x - playerPos.x) * 180 / PI + 270;

	if (abs(tankBodyAngle - angle) < 30 || abs(tankBodyAngle - angle) > 330) {
		if (playerLife) {
			tankGun.setRotation(angle);
			switcher.shoot = true;
		}
		else {
			switcher.shoot = false;
		}
	}
	else {
		switcher.shoot = false;
	}


	if (decisionTime <= 0) {
		decisionTime = (100 + static_cast<float>(rand() % 3000)) / 10;
		decision = 1 + rand() % 4;
		time = 0;
		if (rand() % 2) {
			if (rand() % 2) {
				decision = SHOT;
				decisionTime = (1000 + static_cast <float> (rand() % 20000)) / 10;
			}
			else {
				decisionTime = (1000 + static_cast <float> (rand() % 3000)) / 10;
				if (tankBodyAngle > 280 && tankBodyAngle < 80) {
					if (tankPos.y < 280) {
						decision = BACKWARD_MOVEMENT;
					}
					else if (tankPos.y > 1440) {
						decision = FORWARD_MOVEMENT;
					}
					else {
						if (rand() % 2) {
							decision = FORWARD_MOVEMENT;
						}
						else {
							decision = BACKWARD_MOVEMENT;
						}
					}
				}
			}
		}
	}

	decisionTime -= deltaTime;

	if (decisionTime > 0) {
		switch (decision) {
		case FORWARD_MOVEMENT:
			switcher.moveForward = true;
			break;
		case BACKWARD_MOVEMENT:
			switcher.moveBackward = true;
			break;
		case ROTATION_LEFT:
			switcher.rotateLeft = true;
			break;
		case ROTATION_RIGHT:
			switcher.rotateRight = true;
			break;
		case SHOT:
			if (angle != tankGun.getRotation()) {
				if (atan2(tankPos.x - playerPos.x, tankPos.y - playerPos.y) < 0) {
					switcher.rotateRight = true;
				}
				else {
					switcher.rotateRight = false;
				}

				if (atan2(tankPos.x - playerPos.x, tankPos.y - playerPos.y) > 0) {
					switcher.rotateLeft = true;
				}
				else {
					switcher.rotateLeft = false;
				}
			}
			else {
				switcher.rotateRight = false;
				switcher.rotateLeft = false;
			}
			break;
		default:
			break;
		}
	}
	else {
		switcher.moveForward = false;
		switcher.moveBackward = false;
		switcher.rotateLeft = false;
		switcher.rotateRight = false;
	}

	// move
	movementSpeed = 0.3 + 0.1 * stats.msLevel;
	tankBodyAngle = tankBodyAngle * PI / 180;

	if (switcher.rotateLeft) {
		tankBody.rotate(-rotationSpeed * deltaTime);
		tankGun.rotate(-rotationSpeed * deltaTime);
		return;
	}

	if (switcher.rotateRight) {
		tankBody.rotate(rotationSpeed * deltaTime);
		tankGun.rotate(rotationSpeed * deltaTime);
		return;
	}

	if (switcher.moveForward) {
		tankBody.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	if (switcher.moveBackward) {
		tankBody.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	// collision
	if (tankPos.x < RIGHT_SHORE_X) {
		tankBody.setPosition(RIGHT_SHORE_X, tankPos.y);
		tankGun.setPosition(RIGHT_SHORE_X, tankPos.y);
	}

	if (tankPos.x > RIGHT_BORDER_X) {
		tankBody.setPosition(RIGHT_BORDER_X, tankPos.y);
		tankGun.setPosition(RIGHT_BORDER_X, tankPos.y);
	}

	float higher_border_y = 260 * sqrt(1 - pow(tankPos.x - 960, 2) / 3450306) - 50;

	if (tankPos.y < higher_border_y) {
		tankBody.setPosition(tankPos.x, higher_border_y);
		tankGun.setPosition(tankPos.x, higher_border_y);
	}

	if (tankPos.y > LOWER_BORDER_Y) {
		tankBody.setPosition(tankPos.x, LOWER_BORDER_Y);
		tankGun.setPosition(tankPos.x, LOWER_BORDER_Y);
	}
}


void TankBot::kill()
{
	if (respawnTime > 0) {
		tankBody.setPosition(-300, -300);
		tankGun.setPosition(-300, -300);
		switcher.shoot = false;
		respawnTime -= deltaTime;
	}
	else {
		tankBody.setPosition(1420, 500);
		tankGun.setPosition(1420, 500);
		stats.healingPoints = 100;
		respawnTime = 3000;
	}
}


TankBot::~TankBot()
{
}