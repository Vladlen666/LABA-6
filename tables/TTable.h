#pragma once
#include <string.h>
#include "polinom.hpp"

class PolinomObj {
private:
  std::string name;
  std::string strPol;
  Polinom pol;

  PolinomObj(std::string _name, std::string _strPol) : name(_name), strPol(_strPol) {
    pol = Polinom(_strPol);
  };

  PolinomObj(std::string _name, Polinom _pol) : name(_name), pol(_pol) {
    strPol = pol.ToString();
  }

public:
  static std::shared_ptr<PolinomObj> Create(std::string _name, std::string _strPol) {
    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, _strPol));
    return shptr;
  }

  static std::shared_ptr<PolinomObj> Create(std::string _name, Polinom pol) {
    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, pol));
    return shptr;
  }

  std::string& getName() { return name; }
  std::string& getStrPol() { return strPol; }
  Polinom& getPol() { return pol; }

  bool operator==(const PolinomObj& other) const noexcept { return name == other.name; }
  bool operator!=(const PolinomObj& other) const noexcept { return name != other.name; }
  bool operator<(const PolinomObj& other) const noexcept { return name < other.name; }
  bool operator>(const PolinomObj& other) const noexcept { return name > other.name; }

  friend bool operator==(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name == s; }
  friend bool operator!=(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name != s; }
  friend bool operator>(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name > s; }
  friend bool operator<(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name < s; }

  friend std::ostream& operator<< (std::ostream& out, const std::shared_ptr<PolinomObj>& polObj) {
    out << polObj->name.substr(0, 9) << " = " << polObj->strPol.substr(0, 19);
    return out;
  }

};

class TTable {
public:
  virtual void Insert(std::shared_ptr<PolinomObj>) = 0;
  virtual std::shared_ptr<PolinomObj>* Find(std::string) = 0;
  virtual void Delete(std::string) = 0;
  virtual void Print() = 0;
  virtual int getCurSize() = 0;
  virtual ~TTable() = 0 {}
};
