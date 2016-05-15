all:
	g++ -c -std=c++11 Coursework/gamedef.h Coursework/Bullet.h Coursework/Game.h Coursework/GameInterface.h Coursework/Map.h Coursework/Menu.h Coursework/MouseCursor.h Coursework/Tank.h Coursework/TankBot.h Coursework/Bullet.cpp Coursework/Game.cpp Coursework/GameInterface.cpp Coursework/main.cpp Coursework/Map.cpp Coursework/Menu.cpp Coursework/MouseCursor.cpp Coursework/Tank.cpp Coursework/TankBot.cpp
	g++ -std=c++11 main.o Bullet.o Menu.o Game.o GameInterface.o Map.o MouseCursor.o Tank.o TankBot.o -o Release/Tanks-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	rm -rf main.o Bullet.o Menu.o Game.o GameInterface.o Map.o MouseCursor.o Tank.o TankBot.o

