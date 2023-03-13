#pragma once
#include <string>
#include <vector>
#include <map>
#include "stack.hpp"
#include "polinom.hpp"
#include "TableManager.h"

using std::string;
using std::vector;
using std::map;

class Operations // �����, �������� �������������� ��������
{
private:
  map<string, vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() {// ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
    ops.emplace("*", vector<int>{ 2, 2 });
    ops.emplace("+", vector<int>{ 1, 2 });
    ops.emplace("-", vector<int>{ 1, 2 });
    ops.emplace("(", vector<int>{ 0, 0 });
    ops.emplace(")", vector<int>{ 0, 0 });
    ops.emplace("d", vector<int>{ 3, 1 });
    ops.emplace("I", vector<int>{ 3, 1 });
  }

  static string str_op() { return string("*, +, -, (, ), d()/dv, I()"); }

  bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  int GetPriority(const string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int GetArity(const string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  Polinom Calc(const string& elem, Polinom left, Polinom right = Polinom()) {// ���������
    if (elem == "*")
      return left * right;
    if (elem == "+")
      return  left + right;
    if (elem == "-")
      return left - right;
    if (elem == "d")
      return left.Differentiate(right.ToString()[0]);
    if (elem == "I")
      return left.Integrate(right.ToString()[0]);

    return Polinom(std::to_string(DBL_MAX)); // when something goes wrong
  }
};

class TPostfix {
private:
  vector<string> infix;
  vector<string> postfix;
  Operations operation;
  TPostfix(const TPostfix&) = delete; // ������ �� �����������
  void operator=(const TPostfix&) = delete; // ������ �� ������������
  bool BracketsCorrect(const string& str) const; // �������� �� ������������ ����������� ������ � ���������� �� ���� ������
  void ToInfix(const string& str); // �������������� ���������� ������ � vector<string> infix
  void ToPostfix(); // �������������� infix � vector<string> postfix
  bool IsMonom(const string& lexem);
  bool IsNumber(const string& lexem);
  void DeleteSpaces(string& str);
  string IsDiff(const char& str);
  TableManager* tableManager;
public:
  TPostfix(string str, TableManager* tb = nullptr) {// �����������
    if (!BracketsCorrect(str))
      throw string("The brackets in expression are incorrect");
    tableManager = tb;
    ToInfix(str);
    ToPostfix();
  }
  vector<string> GetInfix() const { return infix; }
  vector<string> GetPostfix() const { return postfix; }

  string GetStringInfix() const {
    string tmp;
    for (const string& elem : infix)
      tmp += elem + ' ';
    return tmp;
  }

  string GetStringPostfix() const {
    string tmp;
    for (const string& elem : postfix)
      tmp += elem + ' ';
    return tmp;
  }

  Polinom Calculate();
};
