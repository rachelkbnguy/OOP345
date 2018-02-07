/************************************
* Name: KHAI BINH NGUY
* StudentID: 126463165
* Title: milestone 3
*************************************/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

//TASK CLASS
class Task {
  std::string name, slots{ "1" }, pass, fail;
public:
  Task() {};
  Task(std::vector<std::string>& line) {
    switch (line.size()) {
    case 4:
      if (validTaskName(line[3]))
        fail = line[3];
      else
        throw std::string("fail task name not understood -->") + line[3] + "<--";
    case 3:
      if (validTaskName(line[2]))
        pass = line[2];
      else
        throw std::string("pass task name not understood -->") + line[2] + "<--";
    case 2:
      if (validSlots(line[1]))
        slots = line[1]; //the number of slots
      else
        throw std::string("slotz not understood -->") + line[1] + "<--";
    case 1:
      if (validTaskName(line[0]) && !line[0].empty())
        name = line[0];
      else
        throw std::string("task name not understood -->") + line[0] + "<--";
      if (slots.empty())
        slots = "1";

      break;
    }
  }
  void print() {
    std::cout << "|name|Slots|pass|fail|="
      << "|" << name
      << "|" << slots
      << "|" << pass
      << "|" << fail
      << "|\n";
  }
  void graph(std::fstream& gv) {
    if (pass.empty() && fail.empty())
      gv << '"' << name << '"' << "[shape=box];\n";
    if (!(pass.empty()))
      gv << '"' << name << '"'
      << "->"
      << '"' << pass << '"'
      << "[color=green];\n";
    if (!(fail.empty()))
      gv << '"' << name << '"'
      << "->"
      << '"' << fail << '"'
      << "[color=red];\n";
  }
};

//TASKMANAGER CLASS
class TaskManager {
  std::vector<Task>taskList;
public:
  TaskManager(std::vector < std::vector<std::string>> & csvData) {
    for (auto& line : csvData) {
      try {
        taskList.push_back(Task(line));
      }
      catch (const std::string& e) {
        std::cerr << "Problem: " << e << "\n";
      }
    }
  }
  void print() {
    for (auto& t : taskList)
      t.print();
  }

  void graph(std::string filename) {
    std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
    if (gv.is_open()) {
      gv << "digraph taskGraph{\n";
      for (auto& t : taskList)
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
int main(int argc, char** argv)
{
  if (argc != 3) {
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

    TaskManager om(csvData);
    om.print();
    om.graph(filename);

    return 0;
  }
  catch (const std::string& e) {
    std::cerr << "It trew --> "<< e<< "\n";
  }
  return 1;
}
				