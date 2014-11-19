#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

int
main(int argc, char** argv) {

  if (argc != 2) {
    std::cerr << "Enter a number to get it's largest prime factor" << std::endl;
    return 1;
  }
 
  std::stringstream inputSS(argv[1]);
  long int inputNum;
  if (!(inputSS >> inputNum)) {
    std::cerr << "Enter a number to get it's largest prime factor" << std::endl;
    return 1;
  }

  std::vector<int> factor;
  for (int i = 3; i < inputNum; i+=2) {
    while (!(inputNum % i)) {
      inputNum /= i;
      factor.push_back(i);
    }
  }

  if (inputNum != 0) {
    factor.push_back(inputNum);
  }

  std::cout << "Prime factorization: " << std::endl;
  for (auto itr : factor) {
    std::cout << itr << std::endl;
  }

  return 0;
}
