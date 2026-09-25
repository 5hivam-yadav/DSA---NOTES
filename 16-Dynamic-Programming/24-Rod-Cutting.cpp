/*
Problem: Rod Cutting
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given prices for lengths 1..n and rod length n, maximize revenue with unlimited cuts (unbounded knapsack).
Sample Input: price = [1,5,8,9,10,17,17,20], n = 8
Sample Output: 22
Explanation: Cut 2 + 6 gives 5 + 17 = 22.
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

int rodCutting(vector<int>& price) {
    int n = (int)price.size();
    vector<int> dp(n + 1, 0);
    for (int len = 1; len <= n; len++) {
        int best = 0;
        for (int cut = 1; cut <= len; cut++) {
            best = max(best, price[cut - 1] + dp[len - cut]);
        }
        dp[len] = best;
    }
    return dp[n];
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    int n = 8;

    auto ans = rodCutting(price);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Unbounded: try every first cut, reuse remainder.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
price[i-1] aligns 1-indexed length.
*/
