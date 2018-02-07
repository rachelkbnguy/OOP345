#include <iostream>
#include <fstream>
#include<string>
#include<vector>
// change main name
using namespace std;

void trimSpace(string& s) {
  while (!s.empty() && s[0] == ' ') //first char
    s.erase(0, 1);
  while (!s.empty() && s[s.size()-1] == ' ') // last char
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
  for (size_t line = 0;line<csvData.size(); line++) {
    for (size_t field = 0; field < csvData[line].size();field++) //read line table of line
      cout << "<" << csvData[line][field] << ">"; // read field table of field
    cout << "\n";
  }
  cout << "\n";

  cout << "interator print\n";
  for (auto line = csvData.begin(); line != csvData.end();line++) {
    for (auto field = line->begin(); field != line->end();field++) //interator behave like a pointer
      cout << "{" << *field << "}"; // read field table of field
    cout << "\n";
  }
  cout << "\n";
}
void csvread(string& filename, char sep, vector<vector<string>> &csvData) {
  fstream in(filename, ios::in);
  if (! in.is_open()) {
    throw string("Cannot open file =.= '") + filename + "'";
  }
  //vector<vector<string>>csvData; // set to table
  string line;
  while(getline(in, line)) {
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
bool validtaskName(Std::strings) {
  for (auto c : S) {
    if (not(isalnum(c) or c == ''))
      return false;
    return true;
  }
}
int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << "csv-file csv-seperator\n";
    return 1;
  }
  //note: argv[0] : progrM NAME
  string filename = argv[1]; //1st arg
  char sep = argv[2][0]; //1st char of 2nd arg

  try {
    vector<vector<string>>csvData; // set to table
    csvread(filename, sep,csvData);
    csvPrint(csvData);
    return 0;
  }catch (const string& e) {
    cerr << "It threw -->"<< e << "\n";
  }
  return 1;
}