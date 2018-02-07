//Name: KHAI BINH NGUY  
// ID: 126463165
// Workshop 8 - STL Algorithms
// w8.cpp
#pragma once
#include <numeric>
#include <algorithm>
#include<functional>
#include <vector>
#include <cmath>
using namespace std;

namespace w8 {
  template<typename T>
  class DataTable {
    vector<T> _x;
    vector<T> _y;
    int _FW;
    int _ND;
  public:
    
    DataTable(ifstream& is, int fw, int nd) {
      _FW = fw;
      _ND = nd;
      T x, y;
      if (is.is_open()) {
        while (!is.eof()) {
          is >> x>>y;
          _x.push_back(x);
          _y.push_back(y);
        }
      }
    }

    T mean() const {
      T sum = accumulate(_y.begin(), _y.end(), (T)0);
      T size = _y.size();
      return sum / size;
    }

    T sigma() const {
      T _mean = mean();
      T size = _y.size();
      vector<T> diff(size);
      transform(_y.begin(),_y.end(), diff.begin(), bind2nd(minus<T>(), _mean));
      T sum = inner_product(diff.begin(), diff.end(), diff.begin(), (T)0);
      return (T)sqrt(sum / (size - 1));
    }

    T median() const {
      vector<T> v = _y;
      sort(v.begin(), v.end());
      T t = _y.size();
      return v[t / 2];
    }

    void regression(T& slope, T& y_intercept) const {
      T tatal_xy = inner_product(_x.begin(), _x.end(), _y.begin(), (T)0);
      T tatal_x = accumulate(_x.begin(), _x.end(), (T)0);
      T tatal_y = accumulate(_y.begin(), _y.end(), (T)0);
      T tatal_xx = inner_product(_x.begin(), _x.end(), _x.begin(), (T)0);
      T num = _y.size();
      slope = (num * tatal_xy - tatal_x * tatal_y) / (num * tatal_xx - tatal_x * tatal_x);
      y_intercept = (tatal_y - slope * tatal_x) / num;
    }

    void display(ostream& os) const {
      os << setw(_FW) << setprecision(_ND) << fixed << 'X';
      os << setw(_FW) << 'Y' << endl;
      for (unsigned int i = 0; i < _x.size(); i++) {
        os << setw(_FW) << _x[i] << setw(_FW) << _y[i] << endl;
      }
    }

    friend ostream& operator<<(ostream& os, const DataTable& datatable) {
      datatable.display(os);
      return os;
    }
  };//class
} //namespace
