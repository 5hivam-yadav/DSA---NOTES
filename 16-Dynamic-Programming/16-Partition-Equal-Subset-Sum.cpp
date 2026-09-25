/*
Problem: Partition Equal Subset Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an array, return true if it splits into two equal-sum subsets (subset-sum DP on total/2).
Sample Input: nums = [1,5,11,5]
Sample Output: true
Explanation: Subsets [1,5,5] and [11] both sum to 11.
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
    bool canPartition(vector<int>& a) {
        int sum = accumulate(a.begin(), a.end(), 0);
        if (sum % 2) return false;
        int K = sum / 2;
        vector<char> dp(K + 1, 0);
        dp[0] = 1;
        for (int x : a)
        for (int s = K; s >= x; s--) dp[s] = dp[s] || dp[s - x];
        return dp[K];
    }
};

int main() {
    vector<int> nums = {1, 5, 11, 5};

    Solution sol;
    auto ans = sol.canPartition(nums);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Reduce to subset sum K = total/2.
Time Complexity:
O(n*sum)
Space Complexity:
O(sum)
Key Idea:
Odd sum impossible.
*/
