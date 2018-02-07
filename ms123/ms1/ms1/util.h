#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<vector>




void trimSpace(std::string& s);
void csvPrint(vector<vector<string>> &csvData);
void csvread(string& filename, char sep, vector<vector<string>> &csvData);
bool validIaskName(std::string &s);
bool validItemName(std::string &s);
bool validSequenceNumberName(std::string &s);