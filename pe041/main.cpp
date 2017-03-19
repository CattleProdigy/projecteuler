#include <algorithm>
#include <iostream>
#include <vector>

bool isPrime(const long int in)
{
    if (in % 2 == 0)
        return false;

    const long int end = std::sqrt(in);
    for (long div = 3; div <= end; div += 2)
    {
        if (in % div == 0)
            return false;
    }
    return true;
}

std::vector<long int>
getPandigitals(int n)
{
    // Generate list of digits
    std::vector<int> digits(n);
    std::iota(digits.rbegin(), digits.rend(), 1);

    // Permutate digits
    std::vector<long int> permutations;
    do
    {
        // Construct a number out of digits
        long int pandigitalNumber = 0;
        auto digit = digits.rbegin();
        for (long int tensPlace = 1; digit != digits.rend(); ++digit, tensPlace *= 10)
            pandigitalNumber += *digit * tensPlace;

        permutations.push_back(pandigitalNumber);
    }
    while (std::prev_permutation(digits.begin(), digits.end()));

    return permutations;
}

int
main(int argc, char** argv)
{
    long int largestPandigital = -1;
    for (int n = 4; n <= 9; ++n)
    {
        std::vector<long int> permutations = getPandigitals(n);
        for (auto i : permutations)
        {
            if (isPrime(i) && i > largestPandigital)
            {
                largestPandigital = i;

                // Since we've sorted we can break early knowning
                // that there's nothing larger for this n
                break;
            }
        }
    }

    std::cout << "Largest Pandigital: " << largestPandigital << std::endl;

    return 0;
}
