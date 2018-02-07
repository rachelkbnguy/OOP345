/************************************
* Name: KHAI BINH NGUY
* StudentID: 126463165
* Title: milestone 2
*************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Task.h"

using namespace std;


int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << "csv-file csv-seperator\n";
    return 1;
  }
  //note: argv[0] : progrM NAME
  std::string filename = argv[1]; //1st arg
  char sep = argv[2][0]; //1st char of 2nd arg

  try {
    vector<vector<string>>csvData; // set to table
    csvread(filename, sep, csvData);
    csvPrint(csvData);

    TaskManager tm(csvData);
    tm.print();
    tm.graph(filename);
    
    return 0;
  }
  catch (const string& e) {
    std::cerr << "It threw -->" << e << "\n";
  }
  return 1;
}
