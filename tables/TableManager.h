#pragma once
#include "TTable.h"
#include "AVLTreeTable.h"
#include "ChainHashTable.h"
#include "OpenHashTable.h"
#include "SortArrayTable.h"
#include "UnsortArrayTable.h"
#include "UnsortListTable.h"

#define COUNTTABLES 6

class TableManager {
public:
  enum TableKind {
    UNSORTARR = 0,
    SORTARR,
    OPENHASH,
    CHAINHASH,
    UNSORTLIST,
    AVLTREE,
  };


private:
  TTable* tables[COUNTTABLES];
  int curTableInd = (int)UNSORTARR;
  int curSize, maxSize;

  const std::vector<std::string> TableNames = { "Unsort Array Table", "Sort Array Table",
                                              "Open Hash Table", "Chain Hash Table",
                                              "Unsort List Table", "AVL-Tree Table" };

  void Insert(std::shared_ptr<PolinomObj> obj) {
    if (curSize == maxSize) {
      throw std::string("Too many objects in Table.");
    }
    int sizeBefore = getCurSize();
    for (int i = 0; i < COUNTTABLES; i++) {
      tables[i]->Insert(obj);
    }
    if (sizeBefore != tables[curTableInd]->getCurSize()) {
      ++curSize;
    }
  }

  TableManager(const TableManager& obj) = delete; // Запрещено копирование

  TableManager operator=(const TableManager& obj) = delete; // Запрещено присваивать

public:

  int getCurSize() { return curSize; }
  int getMaxSize() { return maxSize; }
  int getCountTables() { return COUNTTABLES; }
  int getActiveTableInd() { return curTableInd; }
  std::string getTableName(int ind) { return TableNames[ind]; }

  void setActiveTable(int ind) {
    if (ind < 0 || ind >= COUNTTABLES) {
      throw std::string("Invalid index for the active table");
    }
    curTableInd = ind;
  }

  TableManager(int size) : curSize(0), maxSize(size) {
    if (size <= 0)
      throw std::string("The table size is too small");
    tables[UNSORTARR] = new UnsortArrayTable(size);
    tables[SORTARR] = new SortArrayTable(size);
    tables[OPENHASH] = new OpenHashTable(size);
    tables[CHAINHASH] = new ChainHashTable(size);
    tables[UNSORTLIST] = new UnsortListTable();
    tables[AVLTREE] = new AVLTreeTable();
  }

  void Insert(std::string _name, Polinom pol) { Insert(PolinomObj::Create(_name, pol)); }

  void Insert(std::string _name, std::string _strPol) { Insert(PolinomObj::Create(_name, _strPol)); }

  std::shared_ptr<PolinomObj>* Find(std::string name) { return tables[curTableInd]->Find(name); }

  void Delete(std::string _name) {
    if (curSize <= 0) {
      throw std::string("No objects in Table");
    }
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Delete(_name);
    curSize = tables[curTableInd]->getCurSize();
  }

  void Print() {
    if (curSize == 0)
      std::cout << "The table is empty\n";
    tables[curTableInd]->Print();
  }

  ~TableManager() {
    for (int i = 0; i < COUNTTABLES; i++)
      delete tables[i];
  }
};
