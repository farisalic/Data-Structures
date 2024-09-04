#include"PostfixCalc.hpp"
#include<iostream>

int main(int argc, char *argv[])
{
  PostfixCalc kalkulator;
  std::string temp;
  std::cout << "Dobrodošli u PostfixCalc!" << std::endl;

  while(true){
  std::cout << "Unesite vas izraz: " << std::endl;
  std::getline(std::cin, temp);
  kalkulator.clear();
  try{
    kalkulator.izracunaj(temp);
  }
  catch(...){
    std::cout << "Greska!" << std::endl;
  }
  };
  return 0;
}
