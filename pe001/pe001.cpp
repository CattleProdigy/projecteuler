#include <iostream>

int
main(int argc, char** argv) {
  int count = 0;
  for (int i = 1 ; i < 1000 ; ++i) {
    if (!(i%3) || !(i%5))
      count += i;
  }
  std::cout << count << std::endl;
  return 0;
}
