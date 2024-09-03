#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>

int gcd(int numerator, int denominator){
  const int num=numerator;
  const int denom=denominator;
  int shift;
  for(shift=0; ((numerator|denominator) & 1) == 0; ++shift){
    numerator >>=1;
    denominator >>=1;
  }

  while ((numerator & 1) ==0){
    numerator >>= 1;
  }

  while(denominator != 0){
    while((denominator & 1) ==0){
      denominator >>= 1;
    }
    if(numerator > denominator){
      std::swap(numerator, denominator);
    }
    denominator -= numerator;
  }
  return numerator << shift;
}

void Rational::skrati(){
  int skrati_sa = gcd(numerator_, denominator_);
  numerator_=numerator_/skrati_sa;
  denominator_=denominator_/skrati_sa;
};

void Rational::predznak(){
  if(denominator_<0){
    denominator_*=-1;
    numerator_*=-1;
  }
};

Rational::Rational(){
  numerator_=0;
  denominator_=1;
};

Rational::~Rational(){};

Rational::Rational(int numerator, int denominator){
  if(denominator==0) throw std::invalid_argument ("Ne moze biti nula");
  else{
    numerator_=numerator;
    denominator_=denominator;
  };
};

Rational::Rational(const std::string& input){
  std::string numerator;
  std::string denominator;
  int predznak;

  auto i=input.begin();

  if(*i=='-'){
    predznak=-1;
    i++;
  }

  for(;i!=input.end(); i++){
    if((*i)>=0 && (*i)<=9) numerator.push_back(*i);
    else if(*i != '/') throw std::invalid_argument("Pogresan unos");
    else if(*i == '/') break;
  };
  numerator_=std::stoi(numerator)*predznak;
  
  if(i==input.end()) denominator=1;
  else{
    if(*i=='/'){
      predznak=1;
      i++;
    }
    if(*i=='-'){
      predznak=-1;
      i++;
    }
    for(;i!=input.end(); i++){
      if(*i>0 && *i<=9) denominator.push_back(*i);
      else throw std::invalid_argument("Pogresan unos");
    }
  }
  denominator_=(std::stoi(denominator))*predznak;
  
  skrati();
};

Rational::Rational(const Rational& rational){
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
};

Rational::Rational(Rational&& rational){
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
  rational.denominator_=0;
  rational.denominator_=1;
};

Rational& Rational::operator=(const Rational& rational){
  if(this!=&rational){
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
  }
    return *this;
};

Rational& Rational::operator=(Rational&& rational){
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
  rational.numerator_=0;
  rational.denominator_=1;
    return *this;
};

Rational Rational::operator+(const Rational& rational)const{
  Rational temp;
  temp.denominator_=denominator_*rational.denominator_;
  temp.numerator_=numerator_*rational.denominator_+denominator_*rational.numerator_;
  temp.skrati();
  temp.predznak();
    return temp;
};

Rational Rational::operator-(const Rational& rational)const{
  Rational temp;
  temp.denominator_=denominator_*rational.denominator_;
  temp.numerator_=numerator_*rational.denominator_-denominator_*rational.numerator_;
  temp.skrati();
  temp.predznak();
    return temp;
};

Rational Rational::operator+(int numerator)const{
  Rational temp;
  temp.denominator_=denominator_;
  temp.numerator_=denominator_+denominator_*numerator;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator-(int numerator)const{
  Rational temp;
  temp.denominator_=denominator_;
  temp.numerator_=denominator_-denominator_*numerator;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator*(const Rational& rational)const{
  Rational temp;
  temp.numerator_=numerator_*rational.numerator_;
  temp.denominator_=denominator_*rational.denominator_;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator*(int numerator)const{
  Rational temp;
  temp.numerator_=numerator_*numerator;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator/(const Rational& rational)const{
  Rational temp;
  temp.numerator_=numerator_*rational.denominator_;
  temp.denominator_=denominator_*rational.numerator_;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator/(int numerator)const{
  if(numerator<0) throw std::invalid_argument("Ne mozes dijeliti sa nulom");
  Rational temp;
  temp.numerator_=numerator_;
  temp.denominator_=denominator_*numerator;
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator^(int power)const{
 Rational temp;
 temp.numerator_=pow(numerator_, power);
 temp.denominator_=pow(denominator_, power);
 temp.skrati();
 temp.predznak();
 return temp;
};

Rational& Rational::operator++(){
  numerator_+=denominator_;
  skrati();
  predznak();
  return *this;
};

Rational& Rational::operator--(){
  numerator_-=denominator_;
  skrati();
  predznak();
  return *this;
};

Rational Rational::operator++(int){
  Rational temp=++(*this);
  temp.skrati();
  temp.predznak();
  return temp;
};

Rational Rational::operator--(int){
  Rational temp=--(*this);
  return *this;
};

bool Rational::operator==(const Rational& rational)const{
  Rational temp1=(*this);
  Rational temp2=rational;
  temp1.skrati();
  temp2.skrati();


  if(temp1.numerator_/temp1.denominator_ == temp2.numerator_/temp2.denominator_) return true;
  else return false;
};

bool Rational::operator==(const char* rational)const{
  Rational temp{rational};
  if(*this==temp) return true;
  else return false;
};


bool Rational::operator!=(const char* rational)const{
  Rational temp{rational};
  if(*this!=temp) return true;
  else return false;
};

bool Rational::operator!=(const Rational& rational)const{
  Rational temp1=(*this);
  Rational temp2=rational;
  temp1.skrati();
  temp2.skrati();
  if(temp1.numerator_/temp1.denominator_ != temp2.numerator_/temp2.denominator_) return true;
  else return false;
};

const int Rational::numerator()const{
  return numerator_;
};

const int Rational::denominator()const{
  return denominator_;
};

std::ostream& operator<<(std::ostream& os, const Rational& rational){
  if(rational.denominator()==1) os<<rational.numerator();
  else os<<rational.numerator()<<'/'<<rational.denominator();
  return os;
};

std::istream& operator>>(std::istream& is, Rational& rational){
  std::string temp;
  std::getline(is, temp);
  rational=Rational{temp};
  return is;
};

