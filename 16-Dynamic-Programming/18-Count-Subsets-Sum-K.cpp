/*
Problem: Count Subsets Sum K
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given an array and k, count subsets summing to k (DP; handle zeros by doubling).
Sample Input: a = [1,1,4,5], k = 5
Sample Output: 3
Explanation: Subsets [1a,4],[1b,4],[5] sum to 5.
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

const int MOD = 1000000007;

int countSubsets(vector<int>& a, int K) {
    vector<int> dp(K + 1, 0);
    dp[0] = 1;
    for (int x : a) {
        for (int s = K; s >= x; s--) {
            dp[s] = (dp[s] + dp[s - x]) % MOD;
        }
        if (x == 0) dp[0] = (dp[0] * 2) % MOD;
    }
    return dp[K];
}

int main() {
    vector<int> a = {1, 1, 4, 5};
    int k = 5;

    auto ans = countSubsets(a, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
0/1 counting backwards;
zeros double the ways.
Time Complexity:
O(n*K)
Space Complexity:
O(K)
Key Idea:
Backward loop avoids reuse;
handle 0 separately.
*/
