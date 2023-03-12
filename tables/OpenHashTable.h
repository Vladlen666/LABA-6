#pragma once
#include "TTable.h"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> data = nullptr;
    bool isNone = true;
    bool isDeleted = false;
  };
  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step;

  unsigned int Hash(const std::string& key) {
    unsigned int h = 0;
    for (char c : key) {
      h = (h * 1664525) + c + 1013904223;
    }
    return h % size;
  }

  unsigned int gcd(unsigned int x, unsigned int y) {
    while (x != 0 && y != 0)
      if (x > y)
        x = x % y;
      else
        y = y % x;
    return x + y;
  }

public:
  OpenHashTable(unsigned int s = 20) : size(s), curSize(0) {
    table = new Bucket[s]();
    step = 1;
    for (unsigned i = 2; i < s / 2 + 1; ++i)
      if (gcd(i, s) == 1)
        step = i;
  }

  ~OpenHashTable() { delete[] table; }

  int getCurSize() { return curSize; }

  void Insert(std::shared_ptr<PolinomObj> data) {
    if (size == curSize) // no free space
      throw std::string("Too many objects in Table.");
    unsigned int h = Hash(data.get()->getName());
    while (!table[h].isDeleted) {
      if (table[h].isNone)
        break;
      if (table[h].data.get()->getName() == data.get()->getName())
        return; // already exist
      else
        h = (h + step) % size;
    }
    table[h] = Bucket{ data, false, false };
    ++curSize;
  }

  std::shared_ptr<PolinomObj>* Find(std::string key) {
    unsigned int h = Hash(key), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return nullptr;
      if (table[h].data.get()->getName() == key)
        return &table[h].data;
      else {
        h = (h + step) % size;
        ++i;
      }
    }
    return nullptr;
  }

  void Delete(std::string key) {
    unsigned int h = Hash(key), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return;
      if (table[h].data.get()->getName() == key) {
        table[h].isDeleted = true;
        --curSize;
      }
      else {
        h = (h + step) % size;
        ++i;
      }
    }
  }

  void Print() {
    for (unsigned i = 0; i < size; ++i)
      if (table[i].isDeleted || table[i].isNone)
        std::cout << i + 1 << ')' << std::endl;
      else
        std::cout << i + 1 << ')' << table[i].data << std::endl;
  }

};

