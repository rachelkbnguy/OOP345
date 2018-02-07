// Workshop 2 - unsigned int, Enumerations, String Class and File I/O 
// w2.cpp
/********************************
NAME: Rachel Khai Binh Nguy
Date: 09/11/2017
STudent: 126463165
Week: 2
********************************/
#include <iostream>
#include "Stations.h"
#include "Station.h"
using namespace w2;

int main(int argc, char* argv[]) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << "\n\n";
	if (argc != 2) {
		std::cerr << "\nIncorrect number of arguments\n";
		return 1;
	}
	w2::Stations stations(argv[1]);
	stations.update();
	stations.restock();
	stations.report();

  return 0;
}