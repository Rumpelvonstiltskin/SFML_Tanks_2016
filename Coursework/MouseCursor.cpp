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

#include "MouseCursor.h"


MouseCursor::MouseCursor(sf::Texture& texture) : hideDelayTime(0)
{
	pickerCursor.setTexture(texture);
	pickerCursor.setTextureRect(sf::IntRect(340, 1925, 50, 50));
	pickerCursor.setOrigin(10, 10);
}


void MouseCursor::update(float deltaTime, sf::Vector2f& mousePos)
{
	if (CURSOR_PICKER_ZONE) {
		showCursor = true;
		pickerCursor.setPosition(mousePos.x, mousePos.y);
		pickerCursor.setColor(sf::Color::White);
		hideDelayTime = 0;
	}
	else {
		hideDelayTime += deltaTime;

		if (hideDelayTime > MOUSE_HIDE_DELAY_TIME) {
			showCursor = false;
		}

		pickerCursor.setPosition(mousePos.x, mousePos.y);
	}
}


void MouseCursor::draw(sf::RenderWindow& window)
{
	if (showCursor) {
		window.draw(pickerCursor);
	}
}


MouseCursor::~MouseCursor()
{
}
