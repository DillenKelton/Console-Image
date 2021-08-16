make: consoleImage.o consoleColor.o
	gcc -o ConsoleImage consoleImage.o consoleColor.o

consoleImage.o: consoleImage.c consoleColor.h
	gcc -c consoleImage.c

consoleColor.o: consoleColor.c consoleColor.h
	gcc -c consoleColor.c

clean:
	del *.o
	del *.exe