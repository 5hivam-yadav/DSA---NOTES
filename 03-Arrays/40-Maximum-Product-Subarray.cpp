/*
Problem: Maximum Product Subarray
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given an integer array, return the maximum product of any contiguous subarray (track both max and min).
Sample Input: nums = [2, 3, -2, 4]
Sample Output: 6
Explanation: Subarray [2, 3] gives product 6.
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
    int maxProduct(vector<int>& a) {
        int b = a[0], mn = a[0], mx = a[0];
        for (size_t i = 1; i < a.size(); i++) {
            int x = a[i];
            if (x < 0) swap(mn, mx);
            mx = max(x, mx * x);
            mn = min(x, mn * x);
            b = max(b, mx);
        }
        return b;
    }
};

int main() {
    vector<int> nums = {2, 3, -2, 4};

    Solution sol;
    auto ans = sol.maxProduct(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Track min+max.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Negative flips extremes.
*/
