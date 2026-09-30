/*
Problem: Zero One Knapsack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given weights, values and capacity W, maximize value picking each
item at most once (0/1 knapsack DP). Sample Input: wt = [1,3,4,5], val =
[1,4,5,7], W = 7 Sample Output: 9 Explanation: Weights 3+4 give value 4+5 = 9.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int knapsack01(vector<int> &wt, vector<int> &val, int W) {
    vector<int> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++) {
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

int main() {
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;

    auto ans = knapsack01(wt, val, W);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Each item once: backward capacity loop.
Time Complexity:
O(n*W)
Space Complexity:
O(W)
Key Idea:
Backward = 0/1, forward = unbounded.
*/
