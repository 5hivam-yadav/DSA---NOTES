/*
Problem: Minimum Coins
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Coin Change
Statement: Given coin denominations and amount, return the minimum coins to make amount, or -1 if impossible (unbounded DP).
Sample Input: coins = [1,2,5], amount = 11
Sample Output: 3
Explanation: 5 + 5 + 1 = 11 with 3 coins.
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
    int coinChange(vector<int>& coins, int amount) {
        const int INF = 1e9;
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for (int c : coins) {
            for (int a = c; a <= amount; a++) {
                dp[a] = min(dp[a], dp[a - c] + 1);
            }
        }
        return dp[amount] == INF ? -1 : dp[amount];
    }
};

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    Solution sol;
    auto ans = sol.coinChange(coins, amount);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Unbounded: forward loop reuses same coin.
Time Complexity:
O(n*amount)
Space Complexity:
O(amount)
Key Idea:
INF init, -1 if unreachable.
*/
