#pragma once
#include <ostream>
#include <cmath>

class Rational {
  public:
  Rational();
  Rational(int numerator, int denominator);
  Rational(const std::string&);
  Rational(const Rational& rational);
  Rational(Rational&& rational);
  Rational& operator=(const Rational& rational);
  Rational& operator=(Rational&& rational);
  Rational operator+(const Rational& rational) const;
  Rational operator+(int numerator) const;
  Rational operator-(const Rational& rational) const;
  Rational operator-(int numerator) const;
  Rational operator*(const Rational& rational) const;
  Rational operator*(int numerator) const;
  Rational operator/(const Rational& rational) const;
  Rational operator/(int numerator) const;
  Rational operator^(int) const;
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  bool operator==(const Rational& rational) const;
  bool operator==(const char* rational) const;
  bool operator!=(const Rational& rational) const;
  bool operator!=(const char* rational) const;
  const int numerator() const;
  const int denominator() const;
  void skrati();
  void predznak();
  ~Rational();

  private:
  int numerator_;
  int denominator_;
};

std::istream& operator>>(std::istream& is, Rational& rational);
std::ostream& operator<<(std::ostream& os, const Rational& rational);
int gcd(const int numerator, const int denominator);
