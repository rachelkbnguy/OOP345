#ifndef _NOTIFICATIONS_H_
#define _NOTIFICATIONS_H_

//#pragma once
// Workshop 5 - Containers
// w5.cpp

/********************************
NAME: Rachel Khai Binh Nguy
Date: 10/04/2017
STudent: 126463165
Week: 5
********************************/

#include "Message.h"

const size_t MSG_MAX = 10;
namespace w5 {
  class Notifications  {
    Message messageTable[MSG_MAX];
    size_t count = 0;
  public:
    void info(std::string label) {
      std::cout << "Notifications("<<label<<"), count = "<<count<<"\n";
    }

    Notifications() {}//- default constructor - empty
     
    Notifications(const Notifications&rhs){ //- copy constructor
           *this = rhs;
  }
  Notifications& operator=(const Notifications& rhs){ //-copy assignment operator
        if (this != &rhs) {
      //delete our brains
      for (size_t i = 0; i < count; i++)
        messageTable[i].reset();
        count = 0;
      //deep copy rhs
      count = rhs.count;
      for (size_t i = 0; i < count; i++)
        messageTable[i] = rhs.messageTable[i];
    }
    return *this;
}
        Notifications(Notifications&&rhs){// - move constructor
               *this = std::move(rhs);
  }
          Notifications&& operator=(Notifications&& rhs){// -move assignment operator
                //delete our brains
            for (size_t i = 0; i < count; i++)
              messageTable[i].reset();
            count = 0;
            //move rhs
            count = rhs.count;
            for (size_t i = 0; i < count; i++) {
              messageTable[i] = std::move(rhs.messageTable[i]);
              rhs.messageTable[i].reset();//return rhs msg into a 'zombie'
            }
            rhs.count=0;//return rhs msg count into a 'zombie'
           return std::move(*this);
  }
        ~Notifications() {}// - destructor
     
        void operator+=(const Message& msg){// - adds msg to the set
          if (count < MSG_MAX) {
            messageTable[count] = msg;
            count++;
          }
          else {
            std::cerr << __FILE__ << ":" << __LINE__ << "/n"
              << "compiled on " << __DATE__ << "at" << __TIME__ << "/n"
              << "messageTable FULL!\n"
              << "increase MESSAGE+_MAX and recompile\n";
            exit(99);
          }
  }
        void display(std::ostream& os) const {//- inserts the Message objects to the os output stream
          for (size_t i= 0; i < count; i++)
            messageTable[i].display(os);
        }
        };
}
#endif