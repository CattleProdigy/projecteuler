#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <cmath>

std::map<int, std::string> epochWord= { {2, "hundred"}, 
                                        {3, "thousand"},
                                        {6, "million"} };

std::map<int, std::string> digitWord = { {0, ""},
                                         {1, "one"}, 
                                         {2, "two"},
                                         {3, "three"}, 
                                         {4, "four"}, 
                                         {5, "five"},
                                         {6, "six"}, 
                                         {7, "seven"},
                                         {8, "eight"},
                                         {9, "nine"} };

std::map<int, std::string> teenWord= { {10, "ten"},
                                       {11, "eleven"}, 
                                       {12, "twelve"},
                                       {13, "thirteen"}, 
                                       {14, "fourteen"}, 
                                       {15, "fifteen"},
                                       {16, "sixteen"}, 
                                       {17, "seventeen"},
                                       {18, "eighteen"},
                                       {19, "nineteen"} };

std::map<int, std::string> tensWord= { {10, "ten"},
                                       {20, "twenty"},
                                       {30, "thirty"}, 
                                       {40, "forty"}, 
                                       {50, "fifty"},
                                       {60, "sixty"}, 
                                       {70, "seventy"},
                                       {80, "eighty"},
                                       {90, "ninety"} };

std::string twoDigitNumber(int i)
{
  if (i < 10)
  {
    return digitWord[i];
  }
  else if (i >= 10 && i < 20)
  {
    return teenWord[i];
  }
  else if (i >= 20 && i <= 99)
  {
    std::stringstream ss;
    ss << tensWord[(i / 10) * 10 ] << digitWord[i % 10]; 
    return ss.str();
  }
  else
  {
    return "FUKKKK";
  }
}

std::string threeDigitNumber(int i)
{
  std::stringstream ss;
  const int hundreds = i / 100;
  if (hundreds > 0 && hundreds <= 9)
  {
    ss << digitWord[hundreds] << "hundred";
  }

  const int twoDigit = i % 100;
  if (hundreds != 0 && twoDigit != 0)
    ss << "and";

  ss << twoDigitNumber(twoDigit);
  return ss.str();
}

int
main(int argc, char** argv)
{

  std::stringstream ss;

  for (int i = 1; i <= 1000; ++i)
  {
    int iTmp = i;

    int digitPlace = std::floor(std::log10(iTmp));
    while (digitPlace > 2)
    {
      int digitEpoch = (digitPlace / 3) * 3; // thousands, millions etc
      int epochBase = iTmp / std::pow(10, digitEpoch); // how many thousands, millions etc

      // Add words from current epoch
      ss << threeDigitNumber(epochBase) << epochWord[digitEpoch];

      // Trim off current epoch from most significant end
      iTmp = iTmp - std::pow(10, digitEpoch) * epochBase;
      digitPlace = std::floor(std::log10(iTmp));
    }
    
    // Add remaining
    ss << threeDigitNumber(iTmp);
  }

  std::cout << ss.str() << std::endl;

  std::cout << "Size: " << ss.str().size();

  return 0;
}
