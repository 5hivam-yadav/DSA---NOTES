/*
Problem: Find Peak Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given an array where neighbours differ, return any peak index
(element greater than both neighbours) in O(log n). Sample Input: nums = [1, 2,
3, 1] Sample Output: 2 Explanation: nums[2] = 3 is greater than 2 and 1.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    int findPeakElement(vector<int> &a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] < a[m + 1])
                lo = m + 1;
            else
                hi = m;
        }
        return lo;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 1};

    Solution sol;
    auto ans = sol.findPeakElement(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Climb slope.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Peak where slope drops.
*/
