
/******************************
Name: KHAI BINH NGUY
Student No.: 126463165
Date: 10/22/2017
*******************************/
#pragma once

template <typename K, typename V, int N>
class KVList {
  K k[N]; //key arr
  V v[N]; //value arr
  size_t count; //number of entries
public:
  KVList() :count(0) {}// - default constructor - adopts a safe empty state

  size_t size() const { //- returns the number of entires in the key - value list
    return count;
  }
  const K& key(int i) const { //- returns an unmodifiable reference to the key of element i in the list  
    if (i < N)
      return k[i];
  }
  const V& value(int i) const //- returns an unmodifiable reference to the value of element i in the list
  {
    if (i < N)
      return v[i];
  }

  KVList& add(const K& kk, const V& vv) //- adds a new element to the list if room exists and returns a reference to the current object, does nothing if no room exists
  {
    if (count < N) {
      k[count] = kk;
      v[count] = vv;
      count++;
    }
    return *this;
  }

  int find(const K& kk) const { //- returns the index of the first element in the list with a key equal to k - defaults to 0
    for (size_t i = 0; i < count; i++) {
      if (k[i] == kk)
        return i;
    }
    return 0;//defaults to 0
  }

  KVList& replace(int i, const K& kk, const V& vv) {// - replaces element i in the list with the key and value received and returns a reference to the current object
    if (i < count) {
      k[i] = kk;
      v[i] = vv;
    }
    return *this;
  }

};//class
