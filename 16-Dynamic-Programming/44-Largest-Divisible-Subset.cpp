/*
Problem: Largest Divisible Subset
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an array, return the largest subset where every pair divides one another (sort + LIS-style DP on a[i] % a[j] == 0).
Sample Input: nums = [1,2,3]
Sample Output: [1,2]
Explanation: 2 % 1 = 0 and 3 % 1 = 0, but 3 % 2 != 0, so the largest chain is [1,2] (or [1,3]).
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
    vector<int> largestDivisibleSubset(vector<int>& a) {
        sort(a.begin(), a.end());
        int n = a.size();
        vector<int> dp(n, 1), par(n, -1);
        int bi = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) if (a[i] % a[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                par[i] = j;
            }
            if (dp[i] > dp[bi]) bi = i;
        }
        vector<int> r;
        for (int i = bi; i != -1; i = par[i]) r.push_back(a[i]);
        return r;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol;
    auto ans = sol.largestDivisibleSubset(nums);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Sort + divide LIS.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Transitive divisibility.
*/
