/*
Problem: Search Rotated II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a rotated sorted array that may contain duplicates and target, return true if target exists. Worst case O(n) when duplicates block halving.
Sample Input: nums = [2, 5, 6, 0, 0, 1, 2], target = 0
Sample Output: true
Explanation: 0 sits at index 3 (or 4).
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
    bool search(vector<int>& a, int x) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo <= hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] == x) return true;
            if (a[lo] == a[m] && a[m] == a[hi]) {
                lo++;
                hi--;
            }
            else if (a[lo] <= a[m]) {
                if (a[lo] <= x && x < a[m]) hi = m - 1;
                else lo = m + 1;
            }
            else {
                if (a[m] < x && x <= a[hi]) lo = m + 1;
                else hi = m - 1;
            }
        }
        return false;
    }
};

int main() {
    vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    int target = 0;

    Solution sol;
    auto ans = sol.search(nums, target);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Shrink duplicates.
Time Complexity:
O(log n) avg, O(n) worst
Space Complexity:
O(1)
Key Idea:
Dup edge shrink.
*/
