/*
Problem: Partition Array Max Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Partition
Statement: Given an array and k, partition into chunks of length <= k maximizing sum of (chunk-max * chunk-length).
Sample Input: arr = [1,15,7,9,2,5,10], k = 3
Sample Output: 84
Explanation: Chunks [15,15,15],[9,9],[10,10]? total 84.
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
    int maxSumAfterPartitioning(vector<int>& a, int k) {
        int n = a.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int mx = 0;
            for (int j = 1; j <= k && i - j >= 0; j++) {
                mx = max(mx, a[i-j]);
                dp[i] = max(dp[i], dp[i-j] + mx * j);
            }
        }
        return dp[n];
    }
};

int main() {
    vector<int> arr = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;

    Solution sol;
    auto ans = sol.maxSumAfterPartitioning(arr, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Last block size.
Time Complexity:
O(nk)
Space Complexity:
O(n)
Key Idea:
Max in tail block.
*/
