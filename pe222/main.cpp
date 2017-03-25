#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <climits>

double
heightDelta(double a, double b)
{
    const double aRadiusLoc = 50. - a;
    const double bRadiusLoc = 50. - b;
    const double radiusLocDiff = aRadiusLoc + bRadiusLoc;
    const double hypotenuse = a + b;

    return std::sqrt(hypotenuse * hypotenuse - radiusLocDiff * radiusLocDiff);
}

double costSavings(double a, double b)
{
    return (a + b) - heightDelta(a, b);
}

int
main(int argc, char**argv)
{
    // Generate list of sphere radii
    std::list<int> sphereRadii(21, 0);
    std::iota(sphereRadii.begin(), sphereRadii.end(), 30);

    // Sweep over initial-sphere choice, because the inner loop
    // is a greedy.
    float bestResult = 99999999999.f;
    for (int i = 0; i < sphereRadii.size(); ++i)
    {
        // Select first sphere to be placed
        std::list<int> sphereRadiiLocal = sphereRadii;
        auto placedSphereItr = sphereRadiiLocal.begin();
        std::advance(placedSphereItr, i);
        int placedSphere = *placedSphereItr;
        sphereRadiiLocal.erase(placedSphereItr);

        int bottomRadius = placedSphere;
        int topRadius = placedSphere;

        std::list<int> resultRadii;
        resultRadii.push_back(placedSphere);

        double currentHeight = 0;
        while (!sphereRadiiLocal.empty())
        {
            // Choose the sphere to place above and below the stack which
            // maximize height savings
            auto topMaximumCostSavingsItr = std::max_element(sphereRadiiLocal.begin(),
                                                             sphereRadiiLocal.end(),
                                                             [topRadius] (const int& a, const int &b) {
                                                                 return (costSavings(topRadius, a) < costSavings(topRadius, b));
                                                             });

            auto bottomMaximumCostSavingsItr = std::max_element(sphereRadiiLocal.begin(),
                                                                sphereRadiiLocal.end(),
                                                                [bottomRadius] (const int& a, const int &b) {
                                                                     return (costSavings(bottomRadius, a) < costSavings(bottomRadius, b));
                                                                });

            const float addedBottomCost = costSavings(bottomRadius, *bottomMaximumCostSavingsItr);
            const float addedTopCost = costSavings(topRadius, *topMaximumCostSavingsItr);

            // Handle the case that a given sphere is optimal for above and below
            if (bottomMaximumCostSavingsItr == topMaximumCostSavingsItr)
            {
                if (addedBottomCost < addedTopCost)
                    bottomMaximumCostSavingsItr = sphereRadiiLocal.end();
                else
                    topMaximumCostSavingsItr = sphereRadiiLocal.end();
            }

            // Place the bottom sphere, push to the result list and the center-to-center height
            if (bottomMaximumCostSavingsItr != sphereRadiiLocal.end())
            {
                resultRadii.push_back(*bottomMaximumCostSavingsItr);
                currentHeight += heightDelta(*bottomMaximumCostSavingsItr, bottomRadius);
                bottomRadius = *bottomMaximumCostSavingsItr;
                sphereRadiiLocal.erase(bottomMaximumCostSavingsItr);
            }

            // Place the top sphere, push to the result list and the center-to-center height
            if (topMaximumCostSavingsItr != sphereRadiiLocal.end())
            {
                resultRadii.push_front(*topMaximumCostSavingsItr);
                currentHeight += heightDelta(*topMaximumCostSavingsItr, topRadius);
                topRadius = *topMaximumCostSavingsItr;
                sphereRadiiLocal.erase(topMaximumCostSavingsItr);
            }
        }

        // Add the top and bottom half of the spheres
        currentHeight += topRadius;
        currentHeight += bottomRadius;

        // Not the best result so far
        if (currentHeight < bestResult)
            bestResult = currentHeight;
    }

    const float MicroPerMilli = 1000.f;
    const int bestResultMicro = bestResult * MicroPerMilli;
    std::cout << "Best: " << bestResultMicro << std::endl;
}
