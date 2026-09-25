/*
Problem: Subset Sum Equals K
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an array and k, return true if some subset sums to k (DP over achievable sums).
Sample Input: a = [3,34,4,12,5,2], k = 9
Sample Output: true
Explanation: Subset [4,5] sums to 9.
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

bool subsetSumToK(vector<int>& a, int K) {
    vector<char> dp(K + 1, 0);
    dp[0] = 1;
    for (int x : a) {
        for (int s = K; s >= x; s--) dp[s] = dp[s] || dp[s - x];
    }
    return dp[K];
}

int main() {
    vector<int> a = {3, 34, 4, 12, 5, 2};
    int k = 9;

    auto ans = subsetSumToK(a, k);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
0/1 subset: iterate sums backwards.
Time Complexity:
O(n*K)
Space Complexity:
O(K)
Key Idea:
Backward = each item used once.
*/
