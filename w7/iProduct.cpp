// Name: KHAI BINH NGUY
// SID: 126463165
// Workshop 7 - STL Containers
// w7.cpp
#include <string>
#include "iProduct.h"
#include "Product.h"
#include "TaxableProduct.h"

namespace w7 {
std::ostream& operator<<(std::ostream& os, const iProduct& product) {
  product.display(os);
  return os;
}

iProduct* readProduct(std::ifstream& in) {
  iProduct* prod;
  char line[14];
  char pNo[6];
  unsigned num;
  char pCost[6];
  double price;
  char taxC;

  in.getline(line, 14); 
                          
  for (int i = 0; i < 5; i++)
    pNo[i] = line[i];
  
  pNo[5] = '\0';
  for (int i = 6; i < 11; i++)
    pCost[i - 6] = line[i];

  pCost[5] = '\0';

  num = atoi(pNo);
  price = atof(pCost);
  taxC = line[12];
 
  if (taxC == 'H' || taxC == 'P') {
    prod = new TaxableProduct(num, price, taxC);
  }
  else {
    prod = new Product(num, price);
  }
  return prod;
}
};