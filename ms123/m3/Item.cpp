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
  std::string name, installer, remover, sequenceNumber, description;
public:
  Order() {};
  Order(std::vector<std::string>& line) {
    switch (line.size()) {
    case 5:
      description = line[4];
    case 4:
      if (validSequenceNumber(line[3]))
        sequenceNumber = line[3];
      else
        throw std::string("sequence number not understood -->") + line[3] + "<--";

      if (validTaskName(line[2]))
        remover = line[2];
      else
        throw std::string("remover number not understand -->") + line[2] + "<--";
      if (validTaskName(line[1]))
        installer = line[1];
      else
        throw std::string("installer name not understand -->") + line[1] + "<--";

      if (validItemName(line[0]) && !line[0].empty())
        name = line[0];
      else
        throw std::string("item name not understand -->") + line[0] + "<--";
    default:
      throw std::string("expected 4, or 5 fields, found ") + std::to_string(line.size());
      break;
    }
  }
  void print() {
    std::string name, installer, remover, sequenceNumber, description;
    std::cout << "|name|installer|remover|sequenceNumber|description|="
      << "|" << name
      << "|" << installer
      << "|" << remover
      << "|" << sequenceNumber
      << "|" << description
      << "|\n";
  }
  void graph(std::fstream& gv) {

    gv << '"' << "Item\n" << name << '"'
      << " -> "
      << '"' << "Installer\n" << installer << '"'
      << "[color=green];\n";

    gv << '"' << "Item\n" << name << '"'
      << " -> "
      << '"' << "Remover\n" << remover << '"'
      << "[color=red];\n";
  }
};
class ItemManager {
  std::vector<Order>itemList;
public:
  ItemManager(std::vector < std::vector<std::string>> & csvData) {
    for (auto& line : csvData) {
      try {
        itemList.push_back(Order(line));
      }
      catch (const std::string& e) {
        std::cerr << "Problem: " << e << "\n";
      }
    }
  }
  void print() {
    for (auto& t : itemList)
      t.print();
  }
  void graph(std::string& filename) {
    std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
    if (gv.is_open()) {
      gv << "digraph itemGraph{\n";
      for (auto& t : itemList)
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


//***********************************************
int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << "task-csv-file task-csv-seperator\n";
    return 1;
  }
  //note: argv[0] : progrM NAME
  std::string filename = argv[1]; //1st arg
  char sep = argv[2][0]; //1st char of 2nd arg

  try {
    std::vector<std::vector<std::string>>csvData; // set to table
    csvread(filename, sep, csvData);
    csvPrint(csvData);

    ItemManager tm(csvData);
    tm.print();
    tm.graph(filename);
    return 0;
  }
  catch (const std::string& e) {
    std::cerr << "It threw -->" << e << "\n";
  }
  return 1;
}

