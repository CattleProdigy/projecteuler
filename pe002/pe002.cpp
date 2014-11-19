#include <iostream>

int
main(int argc, char** argv) {

  int curr = 2;
  int prev = 1;

  int evenCount = 0;

  while (curr <= 4000000) {

    if (!(curr % 2)) // is even
      evenCount += curr;

    int tmp = curr;
    curr = prev + curr;
    prev = tmp;
  }

  std::cout << evenCount << std::endl;

  return 0;

}
