// Name: KHAI BINH NGUY
// SID: 126463165
// Workshop 7 - STL Containers
// w7.cpp
#include "Product.h"

namespace w7 {
  double Product::getCharge() const
  {
    return charge;
  }

  void Product::display(std::ostream& os) const
  {
    os << std::setw(10) << std::right << pID << std::setw(10) << std::right << charge;
  }
}