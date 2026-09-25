/*
Problem: Target Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given numbers and target, count assignments of +/- reaching target (subset sum (total+target)/2).
Sample Input: nums = [1,1,1,1,1], target = 3
Sample Output: 5
Explanation: Five sign assignments yield 3.
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
    int findTargetSumWays(vector<int>& a, int target) {
        int sum = accumulate(a.begin(), a.end(), 0);
        if (abs(target) > sum || (sum + target) % 2) return 0;
        int K = (sum + target) / 2;
        vector<int> dp(K + 1, 0);
        dp[0] = 1;
        for (int x : a) {
            for (int s = K; s >= x; s--) dp[s] += dp[s - x];
            if (x == 0) dp[0] *= 2;
        }
        return dp[K];
    }
};

int main() {
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;

    Solution sol;
    auto ans = sol.findTargetSumWays(nums, target);
    cout << ans << endl;
    return 0;
}

/*
Approach:
+/- assignment = subset with sum (sum+target)/2.
Time Complexity:
O(n*sum)
Space Complexity:
O(sum)
Key Idea:
Same as count-partitions transform.
*/
