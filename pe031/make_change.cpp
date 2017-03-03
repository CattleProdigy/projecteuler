#include<cstdlib>
#include<cstdio>
#include<vector>

using namespace std;

// Prototypes
int make_change(int amount, const vector<int> &denoms, bool print); 
void _h_make_change(int amount, 
                        vector<vector<vector<int>>> &dps, 
                        const vector<int> &denoms); 

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Call make_change with the amount for which you"
                "want change made.\ne.g. ./make_change 200\n");
        return 1;
    }

    int amount = atoi(argv[1]);

    // Novo Scotia Coin denoms
    const int NS_COINS[] = {1, 2, 5, 10, 20, 50, 100, 200};

    // Vector form of NS_Coins
    vector<int> denoms(NS_COINS,
        NS_COINS + sizeof(NS_COINS) / sizeof(NS_COINS[0]));
   
    // Set last argument to true to see all the ways
    int ways = make_change(amount, denoms, false);

    printf("Number of ways to make %i: %i\n", amount, ways);

    return 0;
}

/*
 * Make Change
 *
 * This function will return all the ways of making change 
 * for a given amount. Uses a dynamic programming approach which
 * stores incremental results for later use.
 * 
 * param: amount - The value for which you make change
 * param: denoms - a SORTED vector of coin denominations
 * param: print  - if true, all the ways will be printed
 *
 * returns number ways to make change
 *
 */
int make_change(int amount, const vector<int> &denoms, bool print) {
  
    // Declare and allocate vector for solutions 
    vector<vector<vector<int>>> dyn_prog_solns; 
    dyn_prog_solns.reserve(amount + 1);
    for (int i = 0; i <= amount; ++i) {
        dyn_prog_solns.push_back(vector<vector<int>>());
    }

    // Make change
    _h_make_change(amount, dyn_prog_solns, denoms);

    // Print Result
    if (print) {
        for (auto it_1 = dyn_prog_solns[amount].begin(); 
             it_1 != dyn_prog_solns[amount].end();
             ++it_1) {
            printf("\t");
            for (auto it_2 = it_1->begin(); 
                 it_2 != it_1->end();
                 ++it_2) {
                printf("%i, ", *it_2);
            }
            printf("\n");
        }
        printf("\n");
    }

    return dyn_prog_solns[amount].size();
}

/*
 * Make Change Helper Function
 *
 * Not to be called directly by user
 *
 * param: amount - same as in caller
 * param: dps    - dynamic programming solns, stores previous results 
 * param: denoms - same as in caller
 *
 * returns nothing
 * 
 * Makes change by appending successively larger denominations to
 * values to previously defined ways of making change for smaller amounts
 *
 * Time: O(amount * (# of denominations)
 */
void _h_make_change(int amount, 
                        vector<vector<vector<int>>> &dps, 
                        const vector<int> &denoms) {

    // Base Case (This shouldn't actually happen)
    if (amount == 0) 
        return;

    for (auto it = denoms.cbegin(); *it <= amount ; ++it) {

        // Amount matches candidate coin
        if ((amount - *it) == 0) {
            vector<int> temp;
            temp.push_back(*it);
            dps[amount].push_back(temp);
            break;
        }

        // Recursive Call if there is no predefined value
        if (dps[amount - *it].empty()) {     
            _h_make_change(amount - *it, dps, denoms);
        }
        
        // Previous solutions to be based on
        vector<vector<int>> temp = dps[amount - *it];

        for (auto it_t = temp.begin(); it_t != temp.end(); ++it_t){
            
            // Skip ways that don't preserve order
            if (it_t->back() < *it)
                continue;
            
            // Add the candidate coin to previous solution, append
            it_t->push_back(*it);
            dps[amount].push_back(*it_t);
        }
    }
}
