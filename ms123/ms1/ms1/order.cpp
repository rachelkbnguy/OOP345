#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

using namespace std;
class Order {
  string customer, product;
  vectore<string>itemList;
public:
  Order() {};
  Order(vector<string>& line) {
    if(line.size()<3)
    throw string("expected 3or more fields, found") + to_string(line.size());
    customer = line[0];
    product = line[1];
    for (size_t item = 2; item < line.size(); item++) {
      if (line[item].empty())// ignore empty fields
        continue;
      if (validItemName(line[item]))
        itemList.push_back(move(line[item]));
      else
        throw string("item name not understaood -->") + line[item] + "<--";
    }
  }
  void print() {

    cout << "|customer|product|item1|item2|....="
      << "|" << customer
      << "|" << product;
    for (auto& item : itemList)
        cout  << "|" << item;
     cout << "|\n";

  }
  void graph(fstream& gph) {

    gph << '"' << customer<<"\n" << product << '"' 
      << "->"
      << '"' << "Item\n"<< item << '"'
      << "[color=blue];\n";
  }
};
class ItemManager {
  vector<Order>itemList;
public:
  ItemManager(vector < vector<string>> & csvData) {
    for (auto& line : csvData) {
      try {
        itemList.push_back(Order(line));
      }
      catch (const string& e) {
        cerr << "Problem: " << e << "\n";
      }
    }
  }
  void print() {
    for (auto& t : itemList)
      t.print();
  }
  void graph() {
    fstream gph(fname + ".gph", ios::out | ios::trunc);
    if (gph.isopen()) {
      gph << "digraph itemGraph{\n";
      for (auto& t : itemList)
        t.graph();
      gph << "}\n";
      gph.close();
      //pass the dot.cpp file code 
      //vector<string>dotLocations{....
      //... command passed>>
      //notes: no argc loop
    }

  }
};
void trimSpace(string& s) {
  while (!s.empty() && s[0] == ' ') //first char
    s.erase(0, 1);
  while (!s.empty() && s[s.size() - 1] == ' ') // last char
    s.erase(0, 1);
}
void csvPrint(vector<vector<string>> &csvData) {
  cout << "range-based for print\n";
  for (auto& line : csvData) {
    for (auto& field : line) //read line table of line
      cout << "(" << field << ")"; // read field table of field
    cout << "\n";
  }
  cout << "\n";

  cout << "index print\n";
  for (size_t line = 0; line<csvData.size(); line++) {
    for (size_t field = 0; field < csvData[line].size(); field++) //read line table of line
      cout << "<" << csvData[line][field] << ">"; // read field table of field
    cout << "\n";
  }
  cout << "\n";

  cout << "interator print\n";
  for (auto line = csvData.begin(); line != csvData.end(); line++) {
    for (auto field = line->begin(); field != line->end(); field++) //interator behave like a pointer
      cout << "{" << *field << "}"; // read field table of field
    cout << "\n";
  }
  cout << "\n";
}
void csvread(string& filename, char sep, vector<vector<string>> &csvData) {
  fstream in(filename, ios::in);
  if (!in.is_open()) {
    throw string("Cannot open file =.= '") + filename + "'";
  }
  //vector<vector<string>>csvData; // set to table
  string line;
  while (getline(in, line)) {
    auto cr = line.find('\r');
    if (cr != string::npos)
      line.erase(cr, 1);
    cout << "line-->" << line << "<--\n";
  }

  string field;
  vector<string>fields;
  for (size_t index = 0; index < line.size(); index++) {
    if (line[index] != sep) // sep is comma
      field += line[index]; //if its not comma, add to field string
    else {
      trimSpace(field);
      // fields.push_back(field); //deep copy 
      // field.clear();//throw a brain away
      fields.push_back(move(field)); //do the job as above with move constructor
    }
  }
  trimSpace(field);
  fields.push_back(move(field));
  for (auto& f : fields) {
    cout << "[" << f << "]";
  }
  cout << "\n";

  csvData.push_back(move(fields));
  /*
  //csvPrint
  for (auto& line : csvData) {
  for (auto& field : line) //read line table of line
  cout << "(" << field << ")"; // read field table of field
  cout << "\n";
  }
  cout << "\n";
  */
  in.close();
}

bool validItemName(std::string s) {
  for (auto c : S) {
    if (not (isalnum(c) or c == ''))
      return false;
    return true;
  }
}

//***********************************************
int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << "task-csv-file task-csv-seperator\n";
    return 1;
  }
  //note: argv[0] : progrM NAME
  string filename = argv[1]; //1st arg
  char sep = argv[2][0]; //1st char of 2nd arg

  try {
    vector<vector<string>>csvData; // set to table
    csvread(filename, sep, csvData);
    csvPrint(csvData);

    ItemManager tm(csvData);
    tm.print();
    tm.graph(fname);
    return 0;
  }
  catch (const string& e) {
    cerr << "It threw -->" << e << "\n";
  }
  return 1;
}

bool validItemName(std::string s);
bool validSequenceNumberName(std::string s);