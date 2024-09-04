#include <iostream>
#include <string>
#include <stack>

bool boltic(const std::string& temp){
std::stack<char> zagrade;

for (char x : temp)
{
  switch (x)
  {
  case '{':
    if (zagrade.top() != '[' || zagrade.top() != '(' || zagrade.top() != '<') zagrade.push(x);
    break;

  case '[':
    if (zagrade.top() != '(' || zagrade.top() != '<') zagrade.push(x);
    break;

  case '(':
    if (zagrade.top() != '<') zagrade.push(x);
    break;

  case '<':
    zagrade.push(x);
    break;

  case '>':
    if (zagrade.empty() || zagrade.top() != '<') return false;
    else zagrade.pop();
    break;

  case ')':
    if (zagrade.empty() || zagrade.top() != '(') return false;
    else zagrade.pop();
    break;

  case ']':
    if (zagrade.empty() || zagrade.top() != '[') return false;
    else zagrade.pop();
    break;

  case '}':
    if (zagrade.empty() || zagrade.top() != '{') return false;
    else zagrade.pop();
    break;

  default:
    return false;
  }
}
};

int main(int argc, char *argv[])
{
  std::string temp;
  std::cout << "BOLTIC" << std::endl;

  while(true){
    std::cout << "Unesite vas izraz: " << std::endl;
    std::getline(std::cin, temp);

    if(boltic(temp) == true) std::cout << "dobar" << std::endl;
    else std::cout << "pogresan" << std::endl;
}
  return 0;
};
