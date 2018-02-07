// Name: KHAI BINH NGUY
// SID: 126463165
// Workshop 7 - STL Containers
// w7.cpp
#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include "Product.h"
#include "TaxableProduct.h"

namespace w7
{
  class Sale
  {
  private:
    std::vector<iProduct*> Products;
  public:
    Sale(const char* filename);
    void display(std::ostream& os) const;
    ~Sale();
  };
}