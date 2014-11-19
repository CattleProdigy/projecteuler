#include <algorithm>
#include <iostream>
#include <vector>

int
main(int argc, char** argv) {

  std::vector<int> multiplicands;
  for (int i = 2; i <= 20; ++i) {
    multiplicands.push_back(i);
  }

  for (auto mult = multiplicands.begin(); mult != multiplicands.end()-1; ++mult) {
    if (*mult == 1)
      continue;

    for (auto otherMult = mult+1; otherMult != multiplicands.end(); ++otherMult) {
      if (!(*otherMult % *mult)) {
        *otherMult /= *mult;
        continue;
      } 
      if (*mult > *otherMult)
        continue;
    }
  }

  long result = 1;
  for (auto mult : multiplicands) {
    result *= mult;
  }

  std::cout << result << std::endl;

  /* brute search */
  //auto divisLambda = [](int a, int b) {return !(a % b);};
  //for (int i = 1*2*3*5*7*11*13*17*19; i < maxVal; ++i) {

  //  if (std::all_of(divisors.begin(), divisors.end(), std::bind(divisLambda, i, std::placeholders::_1))) {
  //    std::cout << i << std::endl;
  //    return 0;
  //  }
  //} 
  return 0;
}
