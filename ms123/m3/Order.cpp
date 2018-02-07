/************************************
* Name: KHAI BINH NGUY
* StudentID: 126463165
* Title: milestone 3
*************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"


class Order {
  std::string customer, product;
  std::vector<std::string>itemList;
public:
  Order() {};
  Order(std::vector<std::string>& line) {
    if (line.size()<3)
      throw std::string("expected 3or more fields, found") + std::to_string(line.size());
    customer = line[0];
    product = line[1];
    for (size_t item = 2; item < line.size(); item++) {
      if (line[item].empty())// ignore empty fields
        continue;
      if (validItemName(line[item]))
        itemList.push_back(move(line[item]));
      else
        throw std::string("item name not understood -->") + line[item] + "<--";
    }
  }
  void print() {

    std::cout << "|customer|product|item1|item2|....="
      << "|" << customer
      << "|" << product;
    for (auto& item : itemList)
      std::cout << "|" << item;
    std::cout << "|\n";

  }
  void graph(std::fstream& gv) {
    for (auto& item : itemList)
    gv << '"' << customer << "\n" << product << '"'
      << "->"
      << '"' << "Item\n" << item << '"'
      << "[color=blue];\n";
  }
};


class OrderManager {
  std::vector<Order>orderList;
public:
  OrderManager(std::vector < std::vector<std::string>> & csvData) {
    for (auto& line : csvData) {
      try {
        orderList.push_back(Order(line));
      }
      catch (const std::string& e) {
        std::cerr << "Problem: " << e << "\n";
      }
    }
  }
  void print() {
    for (auto& t : orderList)
      t.print();
  }
  void graph(std::string filename) {
    std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
    if (gv.is_open()) {
      gv << "digraph itemGraph{\n";
      for (auto& t : orderList)
        t.graph(gv);
      gv << "}\n";
      gv.close();
      std::vector<std::string> dotLocations{
        "C:\/\Program Files (x86)\/graphviz-2.38/release/bin/dot.exe",
        //     R"("C:"Program Files(x86)"graphviz - 2.38 release bin dot.exe")",

      };

      std::string dot;
      for (auto& e : dotLocations) {
        auto fileexist = [](std::string filename) {std::fstream f(filename, std::ios::in); return f.is_open(); };
        if (fileexist(e)) {
          dot = move(e);
          break;
        }
      }

      if (dot.empty()) {
        std::cerr << R"foo(Graphviz program "dot" not found! Package "graphviz" is not installed.)foo";
        return;
      }
      std::string cmd = dot;
      cmd += " -Tpng C:\/\Users\/rache/OneDrive/Documents/Seneca/Semester3/OOP345/milestone/m3/m3/" + filename + ".gv -o C:\/\Users\/rache/OneDrive/Documents/Seneca/Semester3/OOP345/milestone/m3/m3/" + filename + ".gv.png";
      std::cout << "Running command -->" << cmd << "<--\n";

    }

  }
};

/**************************************/
int main(int argc, char** argv)
{
	if(argc != 3) {
    std::cerr << "Usage: " << argv[0] << " item-csv-file item-csv-separator\n";
		return 1;
	}
  //note: argv[0] : progrM NAME
  std::string filename = argv[1]; //1st arg
  char sep = argv[2][0]; //1st char of 2nd arg

  try {
    std::vector<std::vector<std::string>>csvData; // set to table
    csvread(filename, sep, csvData);
    csvPrint(csvData);
		
		OrderManager om(csvData);
		om.print();
		om.graph(filename);
		
		return 0;
	} catch (const std::string& e) {
		std::cerr << "It trew --> " << e << "\n";
	}
	return 1;
}