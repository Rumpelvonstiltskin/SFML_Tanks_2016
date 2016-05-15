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
typedef short int si;

enum gameStates {
	GAME, OPTIONS, ABOUT, EXIT, MENU, PAUSE
};

#define PI 3.14159265

#define OUTSIDE_AREA bulletPos.x > 1920 || bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.y > 1080
#define CURSOR_PICKER_ZONE (mousePos.y > 840) || (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 <= 1)
#define BATTLE_ZONE (mousePos.y < 840) && (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 >= 1)
#define UPGRADE_AREA tankPos.x > 70 && tankPos.x < 100 && tankPos.y > 525 && tankPos.y < 555

#define SECOND 1000
#define MOUSE_HIDE_DELAY_TIME 500
#define UPGRADE_DELAY_TIME 300

#define GUN_LENGTH 120
#define TANK_DAMAGE 20
#define LEFT_SHORE_X 762.5
#define RIGHT_SHORE_X 1177
#define LEFT_BORDER_X 75
#define RIGHT_BORDER_X 1845
#define LOWER_BORDER_Y 767.5
#define HIGHER_BORDER_Y 260 * sqrt(1 - pow(tankPos.x - 960, 2) / 3450306) - 50