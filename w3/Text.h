#pragma once
#include <fstream>
#include<iostream>
#include <string>
using namespace std;
namespace w3 {

  class Text {
    size_t count = 0;
    std::string * dataTable = nullptr;
  public:
    ~Text() {
      delete[] dataTable;
    }
    Text() {

    }
    Text(char* fname) {
      //open file 
      std::fstream in(fname, std::ios::in);
      if (in.is_open()) {
        //count the unmber of line in the file 
        std::string line;
        while (getline(in, line))
          count++;
        std::cout << "File: '" << fname << "' contains " << count << " lines\n";
        // allocate a table to hold the data 
        dataTable = new std::string[count];
        // read the data 
        in.clear();//clear the end-of-file(EOP) error state //go back to begining
        in.seekp(0);//back to head file
        for (size_t i = 0; i < count; i++) {
          getline(in, dataTable[i]);
      /*    auto cr = dataTable[i].find('r'); //r issue
          if (cr != std::string::npos)
          dataTable[i].erase(cr);//eof*/
        }
        // close the file
        in.close();
      }
      else {
        std::cerr << "Cannot open file;" << fname << "\n";
        exit(99);
      }
    }
    Text& operator = (const Text& rhs) {
      if (this != &rhs) {
        cout << "Copy assigment operator\n";
        delete[] dataTable;
        dataTable = nullptr;		// back to zombie
        count = 0;
        if (rhs.dataTable) {		//rhs has brain
          count = rhs.count;		//take size of rhs
          dataTable = new std::string[count];	//make SPACE for brain
                  //duplicate brain like rhs
          for (size_t i = 0; i < count; i++)
            dataTable[i] = rhs.dataTable[i];
        }
      }
      else
        cout << "copy assigment operator --self assignment\n";
      return *this;
    }

    Text& operator =(Text&& rhs) {
      if (this != &rhs) {
        cout << "Move assigment operator\n";
        if (this != &rhs) {
          delete[] dataTable;			//clean the brain // time spent 
          dataTable = rhs.dataTable;		// steal the brain
          count = rhs.count;
          rhs.dataTable = nullptr;		//make rhs into zombie
          rhs.count = 0;
        }
      }
      else
        cout << "move assigment operator --self assignment\n";
      return std::move(*this);
    }
    Text(const Text& rhs) {
      cout << "Copy constructor operator\n";
      *this = rhs;
    }
    Text(Text&& rhs) {
      cout << "Move constructor operator\n";
      *this = std::move(rhs);
    }
    size_t size() {
      return count; // number of text data
    }
  };//class
}//namespace