// Name: KHAI BINH NGUY
// SID: 126463165
// Workshop 7 - STL Containers
// w7.cpp
#pragma once
#include <iostream>
#include <fstream>
#include <string>


namespace w7 {


  class iProduct {
  public:
    virtual double getCharge() const = 0;
    virtual void display(std::ostream&) const = 0;
  };

  std::ostream& operator<<(std::ostream& os, const iProduct& product);

  iProduct* readProduct(std::ifstream& in);
   

};
