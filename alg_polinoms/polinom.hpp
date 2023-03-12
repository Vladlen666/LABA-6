#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "../data_structures/list.hpp"
#define DEG_BIT 4

class Polinom {
private:

  struct Monom {
    double coef;
    unsigned i : DEG_BIT;
    unsigned j : DEG_BIT;
    unsigned k : DEG_BIT;

    Monom() :coef(0), i(0), j(0), k(0) {};

    Monom(double cf, int a, int b, int c) {
      if (a < 0 || a >(1 << DEG_BIT) - 1 || b < 0 || b >(1 << DEG_BIT) - 1 || c < 0 || c >(1 << DEG_BIT) - 1)
        throw std::string("Incorrect monomial degree");
      coef = cf; i = a; j = b; k = c;
    }

    Monom(std::string s) :coef(0), i(0), j(0), k(0) {
      unsigned i1, i2, n;
      for (i1 = 0; i1 < s.size(); ++i1)
        if (!(std::isdigit(s[i1]) || s[i1] == '.' || s[i1] == '-' || s[i1] == '+'))
          break;
      if (i1 == 0) // xyz - first
        coef = 1;
      else if (i1 == 1) {
        if (s[0] == '-')// -x == -1x
          coef = -1;
        else if (s[0] == '+') // +x - not first OR 1
          coef = 1;
        else
          coef = stod(s.substr(0, i1)); // 0-9
      }
      else
        coef = stod(s.substr(0, i1));// get coef

      for (; i1 < s.size(); ++i1) { // i1 point to letter
        for (i2 = i1 + 1; i2 < s.size() && std::isdigit(s[i2]); ++i2) {}
        if (i2 == i1 + 1) { // no degree
          switch (s[i1]) {
          case 'x': i += 1; break; // 2x
          case 'y': j += 1; break;
          case 'z': k += 1; break;
          case ' ': break;
          default: throw std::string("Monom contains unexpected characters");
          }
        }
        else {
          n = stoi(s.substr(i1 + 1, i2 - i1 - 1));
          if (n > (1 << DEG_BIT) - 1)
            throw std::string("Incorrect monomial degree");
          switch (s[i1]) {
          case 'x': i += n; break;
          case 'y': j += n; break;
          case 'z': k += n; break;
          case ' ': break;
          default: throw std::string("Monom contains unexpected characters");
          }
        }
        i1 = i2 - 1;
      }
    }

    bool IsSimilar(const Monom& x)const { // degree
      return ((i == x.i) && (j == x.j) && (k == x.k));
    }

    const Monom& operator=(const Monom& m) {
      coef = m.coef; i = m.i; j = m.j; k = m.k;
      return *this;
    }

    Monom operator+(const Monom& x)const {
      if (!IsSimilar(x))
        throw std::string("Error:\nAn attempt to find the sum of two monomials with different degrees");
      return Monom(coef + x.coef, i, j, k);
    }

    Monom operator-(const Monom& x)const {
      if (!IsSimilar(x))
        throw std::string("Error:\nAn attempt to find the difference of two monomials with different degrees");
      return Monom(coef - x.coef, i, j, k);
    }

    Monom operator-() const {
      return Monom(-coef, i, j, k);
    }

    Monom operator*(const Monom& x)const {
      if ((i + x.i) > (1 << DEG_BIT) - 1 ||
        (j + x.j) > (1 << DEG_BIT) - 1 || (k + x.k) > (1 << DEG_BIT) - 1)
        throw std::string("Overflow of the monomial degree");
      return Monom(coef * x.coef, i + x.i, j + x.j, k + x.k);
    }

    bool operator==(const Monom& x)const {
      if (coef == x.coef && i == x.i && j == x.j && k == x.k)
        return true;
      return false;
    }

    bool operator!=(const Monom& x)const {
      return !(*this == x);
    }

    bool operator<(const Monom& x)const { // lexicographic order
      if ((i < x.i) || (i == x.i && j < x.j) || (i == x.i && j == x.j && k < x.k))
        return true;
      return false;
    }

    bool operator>(const Monom& x) const {
      if ((i > x.i) || (i == x.i && j > x.j) || (i == x.i && j == x.j && k > x.k))
        return true;
      return false;
    }

    bool operator<=(const Monom& x)const {
      if (IsSimilar(x) || *this < x)
        return true;
      return false;
    }

    bool operator>=(const Monom& x)const {
      if (IsSimilar(x) || *this > x)
        return true;
      return false;
    }

    std::string ToString()const {
      std::stringstream out;
      out << *this;
      return out.str();
    }

    friend std::ostream& operator<<(std::ostream& out, const Monom& m) {
      if (m.coef == -1 && m.i == 0 && m.j == 0 && m.k == 0)
        out << "-1";
      else if (m.coef == -1)
        out << '-';
      else if (m.coef != 1 || (m.coef == 1 && m.i == 0 && m.j == 0 && m.k == 0))
        out << m.coef;
      if (m.i != 0) {
        out << 'x';
        if (m.i != 1)
          out << m.i;
      }
      if (m.j != 0) {
        out << 'y';
        if (m.j != 1)
          out << m.j;
      }
      if (m.k != 0) {
        out << 'z';
        if (m.k != 1)
          out << m.k;
      }
      return out;
    }

    friend std::istream& operator>>(std::istream& in, Monom& x) {
      std::string s; in >> s;
      x = Monom(s);
      return in;
    }
  };

  bool static isMonom(std::string s) {
    if (s.empty())
      return false;
    int i; bool dot = false;
    for (i = 0; i < s.size(); ++i) {
      if (!(std::isdigit(s[i]) || s[i] == '.' || s[i] == '-' || s[i] == '+'))
        break;
      if (s[i] == '.')
        if (dot == true) // two dots
          return false;
        else
          dot = true;
    } // coef finished

    for (; i < s.size(); ++i) // i point to letter
      if (!(s[i] == 'x' || s[i] == 'y' || s[i] == 'z'))
        return false;

    return true;
  }

  TList<Monom> pol;

  Polinom(const Monom& x) {
    if (x.coef != 0)
      pol.InsertLast(x);
  }

  Polinom operator+(const Monom& x) {
    Polinom res; auto it = pol.begin();
    while (it != pol.end() && x < (*it)) // before x
      res.pol.InsertLast(*(it++));
    if (it == pol.end()) {
      if (x.coef != 0)
        res.pol.InsertLast(x);
    }
    else {
      if (x.IsSimilar(*it)) {
        if (-x.coef != it->coef)
          res.pol.InsertLast(*(it++) + x);
      }
      else
        res.pol.InsertLast(x);
      while (it != pol.end())
        res.pol.InsertLast(*(it++));
    }
    return res;
  }

public:
  Polinom() {};

  Polinom(const Polinom& x) : pol(x.pol) {};

  Polinom(const std::string& s) {
    unsigned i, j;
    for (i = 0; i < s.size(); ++i) {
      for (j = i + 1; j < s.size() && s[j] != '+' && s[j] != '-'; ++j) {}
      *this = *this + Monom(s.substr(i, j - i));
      i = j - 1;
    }
  }

  std::string ToString() const {
    std::stringstream out;
    out << *this;
    return out.str();
  }

  Polinom& operator=(const Polinom& x) {
    pol = x.pol;
    return *this;
  }

  bool operator==(const Polinom& x) const {
    if (this == &x)
      return true;
    if (pol.GetSize() != x.pol.GetSize())
      return false;
    auto i1 = pol.cbegin(), i2 = x.pol.cbegin();
    while (i1 != pol.cend())
      if (*(i1++) != *(i2++))
        return false;
    return true;
  }

  Polinom operator+(const Polinom& x) const {
    Polinom res; auto it1 = pol.cbegin(), it2 = x.pol.cbegin();
    while ((it1 != pol.cend()) && (it2 != x.pol.cend()))
      if (*it1 > *it2) {
        res.pol.InsertLast(*(it1++));
      }
      else if ((*it1).IsSimilar(*it2)) {
        if (it1->coef == -(it2->coef)) {
          ++it1; ++it2;
        }
        else
          res.pol.InsertLast(*(it1++) + *(it2++));
      }
      else {
        res.pol.InsertLast(*(it2++));
      }
    if (it1 != pol.cend())
      while (it1 != pol.cend())
        res.pol.InsertLast(*(it1++));
    else
      while (it2 != x.pol.cend())
        res.pol.InsertLast(*(it2++));
    return res;
  }

  Polinom operator-(const Polinom& x) const {
    if (this == &x)
      return Polinom();
    Polinom res; auto it1 = pol.cbegin(), it2 = x.pol.cbegin();
    while ((it1 != pol.cend()) && (it2 != x.pol.cend()))
      if (*it1 > *it2) {
        res.pol.InsertLast(*(it1++));
      }
      else if ((*it1).IsSimilar(*it2)) {
        if (it1->coef == it2->coef) {
          ++it1; ++it2;
        }
        else
          res.pol.InsertLast(*(it1++) - *(it2++));
      }
      else {
        res.pol.InsertLast(-*(it2++));
      }
    if (it1 != pol.cend())
      while (it1 != pol.cend())
        res.pol.InsertLast(*(it1++));
    else
      while (it2 != x.pol.cend())
        res.pol.InsertLast(-*(it2++));
    return res;
  }

  Polinom operator-() const {
    Polinom res;
    for (auto it = pol.cbegin(); it != pol.cend(); ++it)
      res = res + -(*it);
    return res;
  }

  Polinom operator*(const Polinom& x) const {
    Polinom res;
    for (auto it1 = x.pol.cbegin(); it1 != x.pol.cend(); ++it1) {
      Polinom tmp;
      for (auto it2 = pol.cbegin(); it2 != pol.cend(); ++it2)
        if ((*it1).coef * (*it2).coef != 0)
          tmp.pol.InsertLast((*it1) * (*it2));
      res = res + tmp;
    }
    return res;
  }

  double Calculate(double a, double b, double c) const {
    double res = 0;
    for (auto it = pol.cbegin(); it != pol.cend(); ++it)
      res += (*it).coef * pow(a, (*it).i) * pow(b, (*it).j) * pow(c, (*it).k);
    return res;
  }

  Polinom Differentiate(char c) const {
    if (!(c == 'x' || c == 'y' || c == 'z')) {
      std::string exc = "Failed to differentiate by variable " + c;
      throw exc;
    }
    Polinom res;
    for (auto p = pol.cbegin(); p != pol.cend(); ++p)
      switch (c) {
      case 'x':
        if ((*p).i != 0)
          res = res + Monom((*p).i * (*p).coef, (*p).i - 1, (*p).j, (*p).k);
        break;
      case 'y':
        if ((*p).j != 0)
          res = res + Monom((*p).j * (*p).coef, (*p).i, (*p).j - 1, (*p).k);
        break;
      case 'z':
        if ((*p).k != 0)
          res = res + Monom((*p).k * (*p).coef, (*p).i, (*p).j, (*p).k - 1);
      }
    return res;
  }

  Polinom Integrate(char c) const {
    if (!(c == 'x' || c == 'y' || c == 'z')) {
      std::string exc = "Failed to integrate by variable " + c;
      throw exc;
    }
    Polinom res;
    for (auto p = pol.cbegin(); p != pol.cend(); ++p)
      switch (c) {
      case 'x':
        if ((*p).i == 15)
          throw std::string("Overflow of the monomial degree in integration by x");
        res = res + Monom((*p).coef / ((*p).i + 1), (*p).i + 1, (*p).j, (*p).k);
        break;
      case 'y':
        if ((*p).j == 15)
          throw std::string("Overflow of the monomial degree in integration by y");
        res = res + Monom((*p).coef / ((*p).j + 1), (*p).i, (*p).j + 1, (*p).k);
        break;
      case 'z':
        if ((*p).k == 15)
          throw std::string("Overflow of the monomial degree in integration by z");
        res = res + Monom((*p).coef / ((*p).k + 1), (*p).i, (*p).j, (*p).k + 1);
      }
    return res;
  }

  friend std::istream& operator>>(std::istream& in, Polinom& x) {
    x = Polinom(); std::string s; unsigned i, j; Monom m;
    getline(in, s); // x  -2x   x+y    
    for (i = 0; i < s.size(); ++i) {
      for (j = i + 1; j < s.size() && s[j] != '+' && s[j] != '-'; ++j) {}
      m = Monom(s.substr(i, j - i));
      if (m.coef != 0)
        x = x + m;
      i = j - 1;
    }
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Polinom& x) {
    if (x.pol.GetSize() == 0) {
      out << '0';
      return out;
    }
    auto it = x.pol.cbegin(); out << *(it++);
    for (; it != x.pol.cend(); ++it) {
      if ((*it).coef >= 0) // > 0
        out << '+';
      out << *it;
    }
    return out;
  }
};
