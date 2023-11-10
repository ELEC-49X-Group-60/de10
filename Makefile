all: hal.o main.o
	g++ -o de10 main.o hal.o

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o -Iinclude/

hal.o: src/HAL.cpp include/HAL.h
	g++ -c src/HAL.cpp -o hal.o -Iinclude/

clean:
	rm ./$(wildcard *.o)
	rm ./de10
