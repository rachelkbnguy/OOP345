/************************************
* Name: KHAI BINH NGUY
* StudentID: 126463165
* Title: milestone 2
*************************************/
#include "Util.h"

void trimSpace(std::string& s) {
  while (!s.empty() && s[0] == ' ') //first char
    s.erase(0, 1);
  while (!s.empty() && s[s.size() - 1] == ' ') // last char
    s.erase(0, 1);
}
void csvPrint(std::vector<std::vector<std::string>> &csvData) {
  std::cout << "*****Range-based for print*****\n";
  for (auto line : csvData) {
    for (auto field : line) //read line table of line
      std::cout << "(" << field << ")"; // read field table of field
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "*****Index print*****\n";
  for (size_t line = 0; line<csvData.size(); line++) {
    for (size_t field = 0; field < csvData[line].size(); field++) //read line table of line
      std::cout << "<" << csvData[line][field] << ">"; // read field table of field
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "*****Interator print*****\n";
  for (auto line = csvData.begin(); line != csvData.end(); line++) {
    for (auto field = line->begin(); field != line->end(); field++) //interator behave like a pointer
      std::cout << "{" << *field << "}"; // read field table of field
    std::cout << "\n";
  }
  std::cout << "\n";
}
void csvread(std::string& filename, char sep, std::vector<std::vector<std::string>> &csvData) {
  std::fstream in(filename, std::ios::in);
  if (!in.is_open()) {
    throw std::string("Cannot open file =.= '") + filename + "'";
  }

  std::string line;
  while (getline(in, line)) {
    auto cr = line.find('\r');
    if (cr != std::string::npos)
      line.erase(cr, 1);
    std::cout << "line-->" << line << "<--\n";


    std::string field;
    std::vector<std::string>fields;

    for (size_t index = 0; index < line.size(); index++) {
      if (line[index] != sep)
        field += line[index]; //if its space, add to field string
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
      std::cout << "[" << f << "]";
    }
    std::cout << "\n";

    csvData.push_back(move(fields));
    std::cout << "\n";
  }
  in.close();
}
bool validTaskName(std::string s) {
  for (auto c : s) {
    if (!(isalnum(c) || c == ' '))
      return false;
    return true;
  }
}
bool validItemName(std::string s) {
  for (auto c : s) {
    if ((!(isalnum(c)) || c == ' '))
      return false;
    return true;
  }
}
bool validSlots(std::string s) {
  for (auto c : s) {
    if (!isdigit(c))
      return false;
    return true;
  }
}
