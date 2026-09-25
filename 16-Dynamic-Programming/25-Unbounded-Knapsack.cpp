/*
Problem: Unbounded Knapsack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given weights, values and capacity with unlimited copies, maximize value (unbounded DP).
Sample Input: wt = [1,3,4,5], val = [6,1,7,7], W = 8
Sample Output: 48
Explanation: Eight copies of weight-1 value-6 give 48.
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

int unbound(vector<int>& wt, vector<int>& v, int W) {
    vector<int> dp(W + 1, 0);
    for (int w = 0; w <= W; w++) for (size_t i = 0; i < wt.size(); i++) if (wt[i] <= w) dp[w] = max(dp[w], dp[w-wt[i]] + v[i]);
    return dp[W];
}

int main() {
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {6, 1, 7, 7};
    int W = 8;

    auto ans = unbound(wt, val, W);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Forward reuse.
Time Complexity:
O(nW)
Space Complexity:
O(W)
Key Idea:
Forward = reuse.
*/
