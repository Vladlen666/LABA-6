#pragma once
#include "TableManager.h"
#include "TPostfix.h"
#include <Windows.h>
#include <stdio.h>

class Interface {

  bool isWorks = true;
  TableManager* tabMan = nullptr;
  const std::vector<std::string> FuncNames = { "Alg Polinoms", "Print Table",
                                               "Insert Elem", "Find Elem", "Delete Elem",
                                               "Cur Information", "Change Active Table",
                                               "Clearing Screen", "Help", "Exit" };

  const std::vector<std::string> AlgPolFuncNames = { "Algebra of polynomials",
                                                     "The value of the polynomial at the point" };

  void(Interface::* modeptr[10])() = { &Interface::mode0, &Interface::mode1, &Interface::mode2,
                                      &Interface::mode3, &Interface::mode4, &Interface::mode5,
                                      &Interface::mode6, &Interface::mode7, &Interface::mode8,
                                      &Interface::mode9 };

  void executableFunc();
  void printFunctions();
  void printTables();
  void setTableManager();
  void algPolinoms();
  void valueInDot();

  std::string getStrPolInInterface();
  std::string getNameInInterface(bool checkUnique = true);

  void mode0(); void mode1(); void mode2();
  void mode3(); void mode4(); void mode5();
  void mode6(); void mode7(); void mode8();
  void mode9();

public:
  Interface() {}
  ~Interface() { delete tabMan; }

  static COORD getPos();
  static void istreamCleaner();
  static void screenCleaner(COORD pos);
  static int Clamp(int border1, int border2);
  static double Clamp(double border1, double border2);

  void Run() {
    while (isWorks) {
      executableFunc();
    }
  }

};
