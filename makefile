make: consoleImage.o consoleColor.o
	g++ -o ConsoleImage consoleImage.o consoleColor.o

consoleImage.o: consoleImage.cpp consoleColor.h
	g++ -c consoleImage.cpp

consoleColor.o: consoleColor.cpp consoleColor.h
	g++ -c consoleColor.cpp