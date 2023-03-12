#pragma once
#include "TTable.h"
#include <vector>

class ChainHashTable final : public TTable {
private:
  std::vector<TList<std::shared_ptr<PolinomObj>>> tables;
  int size;
  int curSize;

  unsigned int Hash(const std::string& key) {
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  ChainHashTable(int sz = 20) : size(sz), tables(sz), curSize(0) {}

  ~ChainHashTable() { tables.clear(); }

  int getCurSize() { return curSize; }

  void Insert(std::shared_ptr<PolinomObj> data) {
    if (Find(data.get()->getName()) != nullptr)
      return;
    else {
      int index = Hash(data.get()->getName());
      tables[index].InsertFirst(data);
      ++curSize;
    }
  }

  std::shared_ptr<PolinomObj>* Find(std::string key) {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (it->get()->getName() == key)
        return &(*it);
    return nullptr;
  }

  void Delete(std::string key) {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (it->get()->getName() == key) {
        tables[index].Delete(it);
        --curSize;
        break;
      }
  }

  void Print() {
    int ind = 0;
    for (size_t i = 0; i < size; i++) {
      std::cout << i << ") ";
      for (auto it = tables[i].begin(); it != tables[i].end(); ++it, ind++) {
        if (ind != 0)
          std::cout << "    ";
        std::cout << *it << '\n';
      }
      if (ind != 0)
        ind = 0;
      else
        std::cout << '\n';
    }
  }
};
