#ifndef _MESSAGE_H
#define _MESSAGE_H
//#pragma once
// Workshop 5 - Containers
// w5.cpp

/********************************
NAME: Rachel Khai Binh Nguy
Date: 10/04/2017
STudent: 126463165
Week: 5
********************************/
#include<iostream>
#include<fstream>
#include<string>

namespace w5 {
  class Message {
    std::string name, reply, tweet;
  public:
    void reset() { //default constructor
      name.clear();
      reply.clear();
      tweet.clear();
    }
    Message() { //default

    }
    Message(std::ifstream& in, char c) {//- constructor retrieves a record from the in file object, parses the record(as described above) and stores its components in the Message object.c is the character that delimits each record
      std::string line;
      getline(in, line, c);
      auto cr = line.find('\r');
      if (cr != std::string::npos)//note position not found
        line.erase(cr);
 
      size_t index = 0;
      //process name
      while (index < line.size() && line[index] != ' ') {
        name += line[index];
        index++;
      }
        //assume hit the space ''
      index++; //skip''
      //process @replay (if present)
      if (index < line.size() && line[index] == '@') {
        index++;//skip '@'
        while (index < line.size() && line[index] != ' ') {
          reply += line[index];
          index++;
        }
        index++;
        }
      //process @tweet (if present)
      while (index < line.size()) { //the end copy everything
        tweet += line[index];
        index++;
      }
     }
  bool empty() const { // - returns true if the object is in a safe empty state

    return tweet.empty();
    }
  
  void display(std::ostream& os) const { //- displays the Message objects within the container
      os << "Message\n"
        << " User  : " << name << "\n";
      if (reply != "\0") {
      os << " Reply : " << reply << "\n";
      }
      os << " Tweet : " << tweet << "\n";
      os << "\n";
    }
  };//class
}//namespace

#endif