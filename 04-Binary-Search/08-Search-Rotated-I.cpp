/*
Problem: Search Rotated I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a rotated sorted array with distinct values and target, return its index or -1 in O(log n).
Sample Input: nums = [4, 5, 6, 7, 0, 1, 2], target = 0
Sample Output: 4
Explanation: 0 sits at index 4.
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
    int search(vector<int>& a, int x) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo <= hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] == x) return m;
            if (a[lo] <= a[m]) {
                if (a[lo] <= x && x < a[m]) hi = m - 1;
                else lo = m + 1;
            }
            else {
                if (a[m] < x && x <= a[hi]) lo = m + 1;
                else hi = m - 1;
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
