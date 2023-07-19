#include <string>
#include <iostream>
#include <clocale>

int main() {
  //setlocale(LC_ALL,"");
  std::string str;
  std::cin >> str;
  if (str == "Дом") {
    std::cout << "Ok";
  }
  return 0;
}