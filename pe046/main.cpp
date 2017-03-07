#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <unordered_set>
#include <set>
#include <cmath>

std::set<long int> primes = {{1}, {2}, {3}};

bool isPrime(const long int in)
{
    // Technically shouldn't happen but whatever
    if (in % 2 == 0)
        return false;

    // Check cached primes (already checked?)
    if (primes.find(in) != primes.end())
    {
        return true;
    }

    long int end = std::sqrt(in);
    for (long div = 3; div <= end; div += 2)
    {
        if (in % div == 0)
            return false;
    }

    // Cache this
    primes.insert(in);

    return true;
}

long int nextPrime(long int after)
{
    auto upperBound = primes.upper_bound(after);
    if (upperBound != primes.end())
    {
        return *upperBound;
    }

    long int primeCandidate = after + after % 2 + 1; // next odd
    for (; !isPrime(primeCandidate); primeCandidate += 2) { }

    return primeCandidate;
}

int
main(int argc, char** argv)
{
    primes.insert(1);
    primes.insert(2);
    primes.insert(3);

    long int i = 3;
    for (;; i += 2)
    {
        if (isPrime(i))
            continue;

        long int currSquare = 1;
        long int primePart = 1;
        long int currSquarePart = 2 * currSquare * currSquare;

        for (; currSquarePart + 1 < i; currSquare++, currSquarePart = 2 * currSquare * currSquare)
        {
            auto p = primes.begin();
            bool exceeded = false;
            primePart = *p;
            while (currSquarePart + primePart < i)
            {
                if (exceeded || p == primes.end())
                {
                    exceeded = true;
                    primePart = nextPrime(primePart);
                }
                else
                {
                    p++;
                    primePart = *p;
                }
            }

            if (currSquarePart + primePart == i)
            {
                long int sum = currSquarePart + primePart;
                printf ("%li: %li + 2 * (%li)^2 = %li\n", i, primePart, currSquare, i);
                break;
            }
        }

        // Print solution and break
        if (currSquarePart + primePart > i)
        {
            printf ("%li: ? + 2 * (?)^2 = ???\n", i);
            break;
        }
    }

    return 0;
}
