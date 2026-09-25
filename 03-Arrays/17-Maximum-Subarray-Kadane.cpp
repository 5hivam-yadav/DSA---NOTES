/*
Problem: Maximum Subarray Kadane
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given an integer array, find the contiguous subarray with the largest sum and return its sum.
Sample Input: nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Sample Output: 6
Explanation: Subarray [4, -1, 2, 1] sums to 6.
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
    int maxSubArray(vector<int>& a) {
        int b = a[0], c = a[0];
        for (size_t i = 1; i < a.size(); i++) {
            c = max(a[i], c + a[i]);
            b = max(b, c);
        }
        return b;
    }
};

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    Solution sol;
    auto ans = sol.maxSubArray(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Extend or restart.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Kadane.
*/
