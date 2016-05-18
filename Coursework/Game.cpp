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

#include "Game.h"
#include "gamedef.h"


void Game::run()
{
	sf::Clock clock;
	float timeSinceLastUpdate = 0;

	while (window.isOpen()) {
		timeSinceLastUpdate = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		processEvents();
		update(timeSinceLastUpdate);
		render();
	}
}


Game::Game() : 
	window(sf::VideoMode(width, height), "SFML Tanks", sf::Style::None), 
	gameState(MENU)
{
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(144);

	if (!gameTexture.loadFromFile("Resources//Game_Texture.png")) exit(1);
	gameTexture.setSmooth(true);

	levelThemeBuffer.loadFromFile("Resources//level_theme.ogg");
	musicTheme.setBuffer(levelThemeBuffer);

	gameInterface = new GameInterface(gameTexture);
	player = new Tank(gameTexture);
	bot = new TankBot(gameTexture);
	dynamicCursor = new MouseCursor(gameTexture);
	map = new Map(gameTexture);
	menu = new Menu;

	musicTheme.setVolume(menu->musicVolumeState * 10);
	musicTheme.setLoop(true);

	sf::View view(sf::FloatRect(0, 0, 1920, 1080));		// design area
	window.setView(view);
}


void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				case sf::Keyboard::Escape:
					if (gameState == MENU) {
						exit(0);
					}
					else {
						gameState = MENU;
					}
					break;
				case sf::Keyboard::Return:
					if (menu->GetPressedItem() == GAME) {
						gameState = GAME;
					}
					if (menu->GetPressedItem() == OPTIONS) {
						gameState = OPTIONS;
					}
					if (menu->GetPressedItem() == ABOUT) {
						gameState = ABOUT;
					}
					if (menu->GetPressedItem() == EXIT) {
						exit(0);
					}
					break;
				default:
					break;
			}
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}
}


void Game::update(float deltaTime)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (gameState == GAME) {
		gameInterface->update(player->stats, deltaTime);
		map->update(deltaTime);
		player->update(deltaTime, bot->getTankPosition(), bot->enemyHit, menu->sfxVolumeState, mousePos);
		bot->update(deltaTime, player->getTankPosition(), player->getFirstBulletPosition(),
					player->life, player->enemyHit, menu->sfxVolumeState);
		dynamicCursor->update(deltaTime, mousePos);
	}

	if (gameState != GAME && gameState !=EXIT)
		menu->update(deltaTime, gameState);
	
	if (gameState == GAME) {
		if (musicTheme.getStatus() == 0)
			musicTheme.play();
			menu->musicTheme.stop();
	}
	else {
		musicTheme.stop();
	}

	if (gameState != GAME) {
		musicTheme.setVolume(menu->musicVolumeState * 10);
	}
}


void Game::render()
{
	window.clear();

	switch (gameState) {
		case MENU:
			menu->draw(window);
			break;
		case GAME:
			map->draw(window);
			if (bot->drawPriority) {
				bot->draw(window);
				player->draw(window);
			} else {
				player->draw(window);
				bot->draw(window);
			}
			gameInterface->draw(window);
			dynamicCursor->draw(window);
			break;
		case OPTIONS:
			menu->draw(window);
			break;
		case ABOUT:
			menu->draw(window);
			break;
		default:
			break;
	}

	window.display();
}


Game::~Game()
{
	delete gameInterface;
	delete player;
	delete bot;
	delete dynamicCursor;
	delete map ;
	delete menu;
}
