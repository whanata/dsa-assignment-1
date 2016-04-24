CC = g++ 
prog: main.o EuroEnglishConverter.o
	$(CC) main.o EuroEnglishConverter.o -o converter
main.o: main.cpp EuroEnglishConverter.h
	$(CC) -c main.cpp
EuroEnglishConverter.o: EuroEnglishConverter.h EuroEnglishConverter.cpp
	$(CC) -c EuroEnglishConverter.cpp
