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
#include <ctime>


#ifdef _WIN32
#include <wtypes.h>
#endif

#ifdef __unix__
#include <X11/Xlib.h>
#endif

int width = 1920;
int height = 1080;


void GetDesktopResolution(int& horizontal, int& vertical)
{
#ifdef _WIN32
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
#endif

#ifdef __unix__
	Display* d = XOpenDisplay(NULL);
	Screen*  s = DefaultScreenOfDisplay(d);
	horizontal = s->width;
	vertical = s->height;
#endif
}


int main()
{
	srand(time(0));

	GetDesktopResolution(width, height);

	Game game;
	game.run();

	return 0;
}
