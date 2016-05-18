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

#include "GameInterface.h"

GameInterface::GameInterface(sf::Texture &texture) : seconds(0), minutes(0), time(0)
{
	gInterface.setTexture(texture);
	gInterface.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	for (int i = 0; i <= 3; ++i) {
		plus[i].setOrigin(20, 20);
		plus[i].setTexture(texture);
		plus[i].setTextureRect(sf::IntRect(390, 1925, 40, 40));
		plus[i].setPosition(450 + i * 300, 1055);
	}

	if (!font.loadFromFile("Resources//bebas.ttf")) exit(1); 

	timeText.setFont(font);
	timeText.setColor(sf::Color::Red);
	timeText.setString("00 : 00");
	timeText.setPosition(923.5, 53);

	playerHealth.setFont(font);
	playerHealth.setPosition(72, 12);
	playerHealth.setColor(sf::Color(255, 1, 1));

	playerArmor.setFont(font);
	playerArmor.setPosition(72, 62);
	playerArmor.setColor(sf::Color(219, 219, 219));

	playerGold.setFont(font);
	playerGold.setPosition(72, 858);
	playerGold.setColor(sf::Color(244,226,27));

	playerMSLevel.setFont(font);
	playerMSLevel.setPosition(72, 914);
	playerMSLevel.setColor(sf::Color(186, 255, 255));

	playerASLevel.setFont(font);
	playerASLevel.setPosition(72, 973);
	playerASLevel.setColor(sf::Color(186, 255, 255));

	playerBSLevel.setFont(font);
	playerBSLevel.setPosition(72, 1029);
	playerBSLevel.setColor(sf::Color(186, 255, 255));
}


void GameInterface::update(struct Tank::stats stats, float deltaTime)
{
	time += deltaTime;

	// game time in ..MM:SS
	if (time >= SECOND) {
		time = 0;
		seconds++;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
			if (minutes < 10) {
				timeText.setString("0"+std::to_string(minutes) + " : 0" + std::to_string(seconds));
			} else {
				timeText.setString(std::to_string(minutes) + " : 0" + std::to_string(seconds));
			}
		}
		else {
			if (seconds < 10) {
				if (minutes < 10) {
					timeText.setString("0" + std::to_string(minutes) + " : 0" + std::to_string(seconds));
				}
				else {
					timeText.setString(std::to_string(minutes) + " : 0" + std::to_string(seconds));
				}
			}
			else {
				if (minutes < 10) {
					timeText.setString("0" + std::to_string(minutes) + " : " + std::to_string(seconds));
				}
				else {
					timeText.setString(std::to_string(minutes) + " : " + std::to_string(seconds));
				}
			}
		}
	}
	
	if (stats.upgradeAvailability == true) {
		if (stats.gold >= 100) {
			for (int i = 0; i <= 3; ++i) {
				plus[i].setColor(sf::Color(255, 255, 0));
			}
		}
	} else {
		for (int i = 0; i <= 3; ++i) {
			plus[i].setColor(sf::Color(217, 217, 217));
		}
	}

	playerHealth.setString("Health : " + std::to_string(stats.healingPoints));
	playerArmor.setString("Armor : " + std::to_string(stats.armor));
	playerGold.setString("Gold : " + std::to_string(stats.gold));
	playerMSLevel.setString("MS   LEVEL : " + std::to_string(stats.msLevel));
	playerASLevel.setString("AS   LEVEL : " + std::to_string(stats.asLevel));
	playerBSLevel.setString("BS   LEVEL : " + std::to_string(stats.bsLevel));
}


void GameInterface::draw(sf::RenderWindow& window)
{
	window.draw(gInterface);
	window.draw(timeText);
	window.draw(playerHealth);
	window.draw(playerArmor);
	window.draw(playerGold);
	window.draw(playerMSLevel);
	window.draw(playerASLevel);
	window.draw(playerBSLevel);
	for (int i = 0; i <= 3; i++) {
		window.draw(plus[i]);
	}
}


GameInterface::~GameInterface()
{
}