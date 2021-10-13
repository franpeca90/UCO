all: main clean

main: main.o algoritmos.o sistemaEcuaciones.o
	g++ main.o algoritmos.o sistemaEcuaciones.o -o main

main.o: main.cpp
	g++ -c main.cpp

algoritmos.o: algoritmos.cpp
	g++ -c algoritmos.cpp

sistemaEcuaciones.o: sistemaEcuaciones.cpp
	g++ -c sistemaEcuaciones.cpp


.PHONY: clean
clean:
	rm *.o
