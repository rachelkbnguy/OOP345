#pragma once
/********************************
NAME: Rachel Khai Binh Nguy
Date: 09/11/2017
STudent: 126463165
Week: 2
********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

namespace w2 {
  enum PassType { PASS_S, PASS_A, P_COUNT }; //#define Pass_st 0 ,Pass_a 1 ,Pass_count 2;

  class Station {
    std::string name;
    unsigned passes[P_COUNT];
  public:
    Station() {
      name = "\0";
      passes[PASS_S] = 0;
      passes[PASS_A] = 0;
    }
    Station(std::fstream& in) {
      std::string line;
      getline(in, line);
      //std::cout << "line= '" << line << "'\n";

      std::string n;
      int index = 0;
      while (index < line.size() && line[index] != ';') {
        n += line[index];
        index++;
      }
      //std::cout << "n='" << n << "'\n";

      if (index == line.size()) {
        std::cerr << "Missing ';' on line ->>" << line << "<<-\n";
      }

      index++;//skip ';' space
              //get student count
      int num = 0;
      while (index < line.size() && isdigit(line[index])) {
        num = 10 * num + line[index] - '0';//'0'=48, everything subtract -> get the value
        index++;
      }
      //std::cout << "num= '" << num << "'\n";
      unsigned s = num;
      if (index == line.size()) {
        std::cerr << "Missing ' ' after student count on line ->>" << line << "<<-\n";
      }
      index++; //skip space
               //get adult count
      num = 0;
      while (index < line.size() && isdigit(line[index])) {
        num = 10 * num + line[index] - '0';//'0'=48, everything subtract -> get the value
        index++;
      }
      // std::cout << "num=" << num << "\n";
      unsigned a = num;
      if (index == line.size()) {
        set(n, s, a);
      }
    }
    void set(const std::string& n, unsigned s, unsigned a) //- sets the instance variables to the values received in its parameters
    {
      name = n;
      passes[PASS_S] = s;
      passes[PASS_A] = a;
    }
    void update(PassType pt, int value)// - updates the number of passes - sold if negative, added if positive
    {
      passes[pt] += value;
    }
    unsigned inStock(PassType pt) const// - returns the number of passes of the requested type
    {
      return	passes[pt];
    }
    const std::string& getName() const //- returns a reference to a string object holding the name of the station
    {
      return name;
    }
    void report() {
      std::cout << std::fixed << std::left << std::setw(22) << getName() << std::setw(6) << inStock(PASS_S) << inStock(PASS_A) << "\n";
    }
    void sales() {
      std::cout << getName() << "\n";
      std::cout << " Student Passes sold : ";
      int s;
      std::cin >> s;
      update(PASS_S, -s);
      std::cout << " Adult   Passes sold : ";
      int a;
      std::cin >> a;
      update(PASS_A, -a);
    }
    void restock() {
      std::cout << getName() << '\n'
        << " Student Passes added : ";
      int s;
      std::cin >> s;
      update(PASS_S, s);
      std::cout << " Adult   Passes added : ";
      int a;
      std::cin >> a;
      update(PASS_A, a);
    }
    void writeOutput(std::fstream& out) {
      out << getName() << ";" << inStock(PASS_S) << " " << inStock(PASS_A) << "\n";
    }
  };//class Station
}//namspace w2