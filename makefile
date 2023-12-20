test: mkdir test.o kalman.o
	g++ -o bin/test bin/test.o bin/kalman.o

kalman.o: mkdir src/point_in_polygon.cpp include/point_in_polygon/point_in_polygon.hpp
	g++ -c src/point_in_polygon.cpp -o bin/kalman.o -I./include

test.o: mkdir src/test.cpp include/point_in_polygon/point_in_polygon.hpp
	g++ -c src/test.cpp -o bin/test.o -I./include

mkdir:
	-mkdir -p bin

clean:
	-rm -r bin/
