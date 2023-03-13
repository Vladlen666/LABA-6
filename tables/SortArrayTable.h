#pragma once
#include "TTable.h"
#include <vector>

class SortArrayTable final : public TTable {
private:

  std::vector<std::shared_ptr<PolinomObj>> row;
  int countElem;

  void AddRewrite(int index) {
    for (int i = countElem - 1; i > index; i--)
      row[i] = row[(i - 1)];
  }

  void DelRewrite(int index) {
    for (size_t i = index; i < countElem; i++) {
      row[i] = row[i + 1];
    }
  }

public:
  SortArrayTable(int sz = 20) : countElem(0), row(sz) {}
  ~SortArrayTable() { row.clear(); }

  int getCurSize() { return countElem; }

  void Insert(std::shared_ptr<PolinomObj> data) {
    int left = 0;
    int right = countElem;
    int lastCompare = 0; //1 - left 2 - right
    int mid = 0;
    if (countElem == row.size()) {
      throw std::string("Too many objects in Table.");
    }
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid] == nullptr) {
        row[mid] = data;
        countElem++;
        return;
      }
      if (data.get()->getName() == row[mid].get()->getName())
        return;
      if (data.get()->getName() > row[mid].get()->getName()) {
        left = mid + 1;
        lastCompare = 1;
      }
      else {
        right = mid - 1;
        lastCompare = 2;
      }
    }
    countElem++;
    if (lastCompare == 1) {
      AddRewrite(left + 1);
      row[left] = data;
    }
    else {
      AddRewrite(right + 1);
      row[right + 1] = data;
    }
  }

  std::shared_ptr<PolinomObj>* Find(std::string key) {
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid].get()->getName() == key)
        return &row[mid];
      else if (row[mid].get()->getName() < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return nullptr;
  }

  void Delete(std::string key) {
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    if (countElem == 0)
      return;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid].get()->getName() == key) {
        countElem--;
        DelRewrite(mid);
        break;
      }
      else if (row[mid].get()->getName() < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
  }

  void Print() {
    for (size_t i = 0; i < countElem; i++) {
      std::cout << i + 1 << ") " << row[i] << std::endl;
    }
  }

};

