/************************************
* Name: KHAI BINH NGUY
* StudentID: 126463165
* Title: milestone 2
*************************************/
#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<vector>

void trimSpace(std::string& s);
void csvPrint(std::vector<std::vector<std::string>> &csvData);
void csvread(std::string& filename, char sep, std::vector<std::vector<std::string>> &csvData);
bool validTaskName(std::string s);
bool validItemName(std::string s);
bool validSlots(std::string s);


