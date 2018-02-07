#pragma once
/********************************
NAME: Rachel Khai Binh Nguy
Date: 09/11/2017
STudent: 126463165
Week: 2
********************************/

#include <iostream>
#include <fstream>
#include <string>
#include "Station.h"


namespace w2 {
	class Stations {
  private:
		int sttCount = 0;
		Station* sttTable = nullptr;
    std::string dataFileName;
	public:
		~Stations() {
      std::fstream out(dataFileName, std::ios::out| std::ios::trunc);
			if (out.is_open()) {
				out << sttCount << ";\n";
				for (int s = 0; s<sttCount; s++)
					sttTable[s].writeOutput(out);
			}
      out.close();
			delete [] sttTable;
		}
		Stations(char *fname) : dataFileName(fname) {
      std::fstream in(fname, std::ios::in);
			if (!in.is_open()) {
        std::cerr << "Cannot open file;" << fname << "\n";
			}
      std::string line;
			getline(in, line);
      //std::cout << "line=" << line << "\n";

			int num = 0;
			int index = 0;
			while (index < line.size() && isdigit(line[index])) {
				num = 10 * num + line[index] - '0';//'0'=48, everything subtract -> get the value
				index++;
			}
      //std::cout << "num=" << num << '\n';
			if(index == line.size()){
        std::cerr << "missing ';' online ->>" << line << "<<-\n";
			}
			if (line[index] != ';') {
        std::cerr<<" expected ';' online ->>" << line << "<<-, found '" <<line[index]<<"'\n";
			}
			index++;//skip ';' space
      if (index == line.size()) { //EOF
        sttCount = num;
        sttTable = new Station[sttCount];
        for (int s = 0; s < sttCount; s++)
          sttTable[s] = Station(in);
      }
			in.close();
		}
		void update() {
      std::cout << "Passes Sold : \n"
                << "------------- \n";
			for (int s = 0; s < sttCount; s++) 
				sttTable[s].sales();
      std::cout << "\n";
		}
		void restock() {
      std::cout << "Passes Added : \n"
                << "-------------- \n";
			for (int s = 0; s < sttCount; s++) 
				sttTable[s].restock();
      std::cout << "\n";
		}
		void report() {
      std::cout << "Passes in Stock : Student Adult \n"
			          << "------------------------------- \n";
				for (int s = 0; s < sttCount; s++) 
					sttTable[s].report();
				
		}
	};//class Stations
}//namespace w2
