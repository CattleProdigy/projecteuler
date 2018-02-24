#include <iostream>
#include <vector>
#include <set>
#include <sstream>


static int charVal(const char c) {
    return static_cast<int>(c - 'A') + 1;
}

class TriangularNumbers
{
    public:
    TriangularNumbers()
    {
        m_triangularNumbers.insert({1, 3, 6, 10, 15, 21, 28, 36, 45, 55});
        m_lastTriangularIdx = 10;
    }

    bool isTriangular(const int x)
    {
        if (m_triangularNumbers.count(x) > 0) {
           return true;
        }

        auto lbound = m_triangularNumbers.lower_bound(x);
        auto ubound = m_triangularNumbers.upper_bound(x);
        if (lbound != m_triangularNumbers.end() && ubound != m_triangularNumbers.end()) {
            return false;
        }

        int largestSoFar = *m_triangularNumbers.rbegin();
        while (largestSoFar < x) {
            m_lastTriangularIdx++;
            largestSoFar = (m_lastTriangularIdx * (m_lastTriangularIdx + 1)) / 2;
            m_triangularNumbers.insert(m_triangularNumbers.end(), largestSoFar);
        }

        return largestSoFar == x;
    }

    private:
    int m_lastTriangularIdx;
    std::set<int> m_triangularNumbers;
};

int main(int argc, const char** argv)
{
    std::stringbuf sb;
    std::cin >> &sb;
    std::string input = sb.str();

    std::vector<std::string> inputs;
    auto lead = input.cbegin();
    auto follow = input.cbegin();
    while (lead != input.cend()) {
        while (lead != input.cend() && (*lead == ',' || *lead == ' ' || *lead == '\"')) {
            ++lead;
            ++follow;
        }
        while (lead != input.cend() && !(*lead == ',' || *lead == ' ' || *lead == '\"')) { ++lead; }
        if (lead != follow) { inputs.emplace_back(follow, lead); }
        follow = lead;
    }

    TriangularNumbers tn;

    int count = 0;
    for (const auto& s : inputs) {
        int sum = 0;
        for (auto c : s) {
            sum += charVal(c);
        }
        count += tn.isTriangular(sum);
    }

    std::cout << count << std::endl;


}
