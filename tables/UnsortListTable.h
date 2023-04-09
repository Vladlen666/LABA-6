#pragma once
#include "TTable.h"
#include "list.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;

public:
  UnsortListTable() {}
  ~UnsortListTable() { }

  int getCurSize() { return list.GetSize(); }

  void Insert(std::shared_ptr<PolinomObj> data) {
    if (Find(data.get()->getName()) != nullptr)
      return;
    list.InsertFirst(data);
  }

  std::shared_ptr<PolinomObj>* Find(std::string name) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name)
        return &(*it);
    return nullptr;
  }

  void Delete(std::string name) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name) {
        list.Delete(it);
        break;
      }
  }

  void Print() {
    int ind = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it, ++ind) {
      std::cout << ind + 1 << ") " << *it << std::endl;
    }
  }

};

