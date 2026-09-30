/*
Problem: Search Insert Position
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array and target, return the index of target or the
position where it would be inserted. Sample Input: nums = [1, 3, 5, 6], target =
5 Sample Output: 2 Explanation: 5 already sits at index 2.
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
    int searchInsert(vector<int> &a, int x) {
        int lo = 0, hi = (int)a.size();
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] < x)
                lo = m + 1;
            else
                hi = m;
        }
        return lo;
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 6};
    int target = 5;

    Solution sol;
    auto ans = sol.searchInsert(nums, target);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Lower bound index.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Insert = lower bound.
*/
