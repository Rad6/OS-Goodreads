all : main

main : utils.h utils.cpp main.cpp
	g++ -std=c++11 utils.h utils.cpp main.cpp -o main

clean:
	rm -f -r main