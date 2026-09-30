/*
Problem: Search Rotated I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a rotated sorted array with distinct values and target, return
its index or -1 in O(log n). Sample Input: nums = [4, 5, 6, 7, 0, 1, 2], target
= 0 Sample Output: 4 Explanation: 0 sits at index 4.
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
    int search(vector<int> &a, int x) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo <= hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] == x)
                return m;
            if (a[lo] <= a[m]) {
                if (a[lo] <= x && x < a[m])
                    hi = m - 1;
                else
                    lo = m + 1;
            } else {
                if (a[m] < x && x <= a[hi])
                    lo = m + 1;
                else
                    hi = m - 1;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    Solution sol;
    auto ans = sol.search(nums, target);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Sorted-half test.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
One half sorted.
*/
