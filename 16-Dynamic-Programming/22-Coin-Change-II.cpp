/*
Problem: Coin Change II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Coin Change
Statement: Given amount and coins, count combinations making amount (unlimited coins, order ignored).
Sample Input: amount = 5, coins = [1,2,5]
Sample Output: 4
Explanation: Four combos: 5; 2+2+1; 2+1+1+1; all 1s.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>
#include <climits>
using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<unsigned long long> dp(amount + 1, 0);
        dp[0] = 1;
        for (int c : coins) {
            for (int a = c; a <= amount; a++) {
                dp[a] += dp[a - c];
            }
        }
        return (int)dp[amount];
    }
};

int main() {
    int amount = 5;
    vector<int> coins = {1, 2, 5};

    Solution sol;
    auto ans = sol.change(amount, coins);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Coin-outer, amount-inner counts combinations not permutations.
Time Complexity:
O(n*amount)
Space Complexity:
O(amount)
Key Idea:
Loop order decides combo vs perm.
*/
