/*
Problem: Binary Search to Find X
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array and target, return the index of target or -1 in O(log n).
Sample Input: nums = [-1, 0, 3, 5, 9, 12], target = 9
Sample Output: 4
Explanation: nums[4] is 9.
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
            else if (a[m] < x) lo = m + 1;
            else hi = m - 1;
        }
        return -1;
    }
};

int main() {
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;

    Solution sol;
    auto ans = sol.search(nums, target);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Classic halve.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Sorted halve.
*/
