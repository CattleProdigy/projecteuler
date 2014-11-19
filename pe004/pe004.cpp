#include <iostream>
#include <sstream>
#include <cmath>

bool isPalindrom(const std::string& str);

int
main(int argc, char** argv) {

  std::stringstream numberSS;
  int currMax = 0;
  for (int i = 999; i >= 100; --i) {
    for (int j = i; j >= 100; --j) {
      numberSS << i*j;
      if (isPalindrom(numberSS.str())) {
        if (i*j > currMax)
          currMax = i*j;
      }
      numberSS.str(std::string());
    }
  } 

  std::cout << "Max: " <<  currMax << std::endl;
  return 0;
}

bool isPalindrom(const std::string& str) {

  auto itr = str.cbegin();
  auto rev_itr = str.crbegin();
  int i = std::floor(str.size() / 2);
  while ((i--)) {
    if (*(itr++) != *(rev_itr++))
      return false;
  }
  return true;
}
