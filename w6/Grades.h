/************************
NAME: KHAI BINH NGUY
ID: 126463165
DATE: 10/11/2017
************************/
#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Grades {
  int* stuID;
  double* grade;
  int count = 0;
public:
  Grades(const std::string fileName) {
    try {
      std::ifstream in(fileName);
      if (in.is_open()) {
        std::string line;
        while (getline(in, line))
          count++;
        in.clear();
        in.seekg(0);
        stuID = new int[count];
        grade = new double[count];
        for (int i = 0; i < count; i++) {
          in >> stuID[i];
          in >> grade[i];
        }
        in.close();
      }
    }
    catch(std::string err) {
      std::cout << err << "\n";

    }
  }
  template<typename Ex>
  void displayGrades(std::ostream& os, Ex lgrade ) const {
    for (int i = 0; i < count; i++) {
     // auto letter = lgrade(grades[i]);
      os << stuID[i] << " " << grade[i] << " " << lgrade(grade[i]) << "\n";
    }
  }
};
