// Name: KHAI BINH NGUY
// SID: 126463165
// Workshop 7 - STL Containers
// w7.cpp
#pragma once
#include <iomanip>
#include "iProduct.h"

namespace w7
{
  class Product : public iProduct
  {
  private:
    unsigned pID;
    double charge;
  public:
    Product(unsigned p, double c) : pID(p), charge(c) {}
    double getCharge() const;
    void display(std::ostream& os) const;
  
  };

}