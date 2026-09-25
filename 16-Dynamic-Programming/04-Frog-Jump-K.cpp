/*
Problem: Frog Jump K
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given stone heights and max jump k, return the minimum energy to reach the end trying all jumps 1..k.
Sample Input: h = [10, 20, 30, 10], k = 3
Sample Output: 20
Explanation: A direct or short-hop path costs 20.
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

int frogK(vector<int>& h, int k) {
    int n = h.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < n; i++) for (int j = 1; j <= k && i - j >= 0; j++) dp[i] = min(dp[i], dp[i-j] + abs(h[i] - h[i-j]));
    return dp[n-1];
}

int main() {
    vector<int> h = {10, 20, 30, 10};
    int k = 3;

    auto ans = frogK(h, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Min over k jumps.
Time Complexity:
O(nk)
Space Complexity:
O(n)
Key Idea:
Window min.
*/
