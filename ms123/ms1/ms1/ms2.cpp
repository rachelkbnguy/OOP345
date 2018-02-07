#include <iostream>
#include <fstream>
#include<string>
#include<vector>




void trimSpace(std::string& s);
void csvPrint(vector<vector<string>> &csvData);
void csvread(string& filename, char sep, vector<vector<string>> &csvData);

bool validtaskName(Std::strings) {
  for (auto c : S) {
    if (not(isaldig(c) or c == ''))
      return false;
    return true;
  }
}