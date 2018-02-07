// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "SecureData.h"

namespace w10 {

  void converter(char* t, char key, int n, const Cryptor& c) {
    for (int i = 0; i < n; i++)
      t[i] = c(t[i], key);
  }

  SecureData::SecureData(const char* file, char key) {
    // open text file
    std::fstream input(file, std::ios::in);
    if (!input)
      throw std::string("\n***Failed to open file ") +
      std::string(file) + std::string(" ***\n");

    // copy from file into memory
    nbytes = 0;
    input >> std::noskipws;
    while (input.good()) {
      char c;
      input >> c;
      nbytes++;
    }
    nbytes--;
    input.clear();
    input.seekg(0, std::ios::beg);
    text = new char[nbytes + 1];

    int i = 0;
    while (input.good())
      input >> text[i++];
    text[--i] = '\0';
    std::cout << "\n" << nbytes << " bytes copied from text "
      << file << " into memory (null byte added)\n";
    encoded = false;

    // encode using key
    code(key);
    std::cout << "Data encrypted in memory\n";
  }

  SecureData::~SecureData() {
    delete[] text;
  }

  void SecureData::display(std::ostream& os) const {
    if (text && !encoded)
      os << text << std::endl;
    else if (encoded)
      throw std::string("\n***Data is encoded***\n");
    else
      throw std::string("\n***No data stored***\n");
  }

  void SecureData::code(char key) {

    //converter(text, key, nbytes, Cryptor());
    
    //part2
    std::thread threat1(std::bind(converter, text, key, nbytes / 2, Cryptor()));
    std::thread threat2(std::bind(converter, text + nbytes / 2, key, nbytes - (nbytes / 2), Cryptor()));
    threat1.join();
    threat2.join();
    
    encoded = !encoded;
  }

  void SecureData::backup(const char* file) {
    if (!text)
      throw std::string("\n***No data stored***\n");
    else if (!encoded)
      throw std::string("\n***Data is not encoded***\n");
    else {
      // open binary file
      std::ofstream os(file, std::ios::binary | std::ios::trunc);
      if (!os)
      {
        throw std::string("\n***File could not be opened***\n");
      }
      // write binary file here
      os.write(text, nbytes);
      os.close();
    }
  }

  void SecureData::restore(const char* filename, char key) {
    // open binary file
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
      throw std::string("\nFile not opened\n");
    }

    // allocate memory here
    if (text)
    {
      delete[] text;
    }
    in.seekg(0, std::ios::end);
    nbytes = (int)in.tellg();
    text = new char[nbytes + 1];
    // read binary file here
    in.seekg(0, std::ios::beg);
    in.read(text, nbytes);
    text[nbytes] = '\0';
    in.close();

    std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
      << filename << " into memory (null byte included)\n";
    encoded = true;

    // decode using key
    code(key);
    std::cout << "Data decrypted in memory\n\n";
  }

  std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
    sd.display(os);
    return os;
  }

}