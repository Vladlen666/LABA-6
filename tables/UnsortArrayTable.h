#pragma once
#include <vector>
#include "TTable.h"

class UnsortArrayTable final : public TTable {
private:
  std::vector<std::shared_ptr<PolinomObj>> data;
  int maxInd;
  int curSize;

public:
  UnsortArrayTable(int sz = 20) : data(sz), maxInd(0), curSize(0) {}
  ~UnsortArrayTable() { data.clear(); }

  int getCurSize() { return curSize; }

  void Insert(std::shared_ptr<PolinomObj> _data) {
    if (data.size() == curSize)
      throw std::string("Too many objects in Table.");
    if (Find(_data->getName()) == nullptr) {
      for (int i = 0; i < data.size(); i++) {
        if (data[i] == nullptr) {
          data[i] = _data;
          if (i == maxInd)
            maxInd++;
          break;
        }
      }
      curSize++;
    }
  }

  std::shared_ptr<PolinomObj>* Find(std::string name) {
    for (int i = 0; i < maxInd; i++)
      if (data[i] != nullptr && data[i].get()->getName() == name)
        return &data[i];
    return nullptr;
  }

  void Delete(std::string name) {
    int i = 0;
    for (; i < maxInd; i++) {
      if (data[i] != nullptr && data[i].get()->getName() == name) {
        data[i] = nullptr;
        curSize--;
        break;
      }
    }

    if (i == maxInd - 1) {
      for (; i >= 0; i--) {
        if (data[i] == nullptr)
          maxInd--;
        else
          break;
      }
    }
  }

  void Print() {
    for (int i = 0; i < maxInd; i++) {
      if (data[i] != nullptr) {
        std::cout << i + 1 << ") " << data[i] << '\n';
      }
      else {
        std::cout << i + 1 << ")\n";
      }
    }
  }
};

