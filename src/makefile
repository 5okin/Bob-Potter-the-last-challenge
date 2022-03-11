output: main.o Engine.o Highscore.o Moving.o Potter.o Gnome.cpp Troll.o
	g++ main.o Engine.o Highscore.o Moving.o Potter.o Gnome.cpp Troll.o -o bobpotter -lncurses

main.o: main.cpp
	g++ -c main.cpp

Engine.o: Engine.cpp
	g++ -c Engine.cpp

Highscore.o: Highscore.cpp
	g++ -c Highscore.cpp

Moving.o: Moving.cpp
	g++ -c Moving.cpp

Potter.o: Potter.cpp
	g++ -c Potter.cpp

Gnome.o: Gnome.cpp
	g++ -c Gnome.cpp

Troll.o: Troll.cpp
	g++ -c Troll.cpp

clean:
	rm *.o