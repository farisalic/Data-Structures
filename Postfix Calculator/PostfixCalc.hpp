#pragma once

#include<string>
#include<stack>
#include<sstream>
#include<iostream>
#include<exception>

class PostfixCalc{
  private:
    std::stack<int> operandi;
    char znak;
  public:
    void clear();
    void izracunaj(std::string& izraz);
};

void PostfixCalc::clear(){
  while(operandi.size()>0) operandi.pop();
}

void PostfixCalc::izracunaj(std::string& izraz){
  clear();
  std::stringstream ss(izraz);
  std::string temp;

  if(izraz.empty()) throw std::invalid_argument("Prazan izraz");

  getline(ss, temp, ' ');
  operandi.push(std::stoi(temp));

  getline(ss, temp, ' ');
  operandi.push(std::stoi(temp));

  getline(ss, temp);
  znak = temp[0];

if(operandi.size()<2) throw std::invalid_argument("Nedovoljno argumenata");
else{
int b=operandi.top();
operandi.pop();
int a=operandi.top();
operandi.pop();

if(znak=='+'){
  std::cout << "Rezultat proracuna je: " << a+b << std::endl;
}
else if(znak=='-'){
  std::cout << "Rezultat proracuna je: " << a-b << std::endl;
}
else if(znak=='*'){
  std::cout << "Rezultat proracuna je: " << a*b << std::endl;
}
else if(znak=='/'){
  if(b==0) throw std::invalid_argument("Dijeljenje sa nulom");
  std::cout << "Rezultat proracuna je: " << a/b << std::endl;
}
}
};

