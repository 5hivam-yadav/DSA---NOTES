/*
Problem: Find Minimum in Rotated
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a rotated sorted array, return its minimum element in O(log n).
Sample Input: nums = [3, 4, 5, 1, 2]
Sample Output: 1
Explanation: The rotation point holds the minimum 1.
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
    int findMin(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] > a[hi]) lo = m + 1;
            else hi = m;
        }
        return a[lo];
    }
};

int main() {
    vector<int> nums = {3, 4, 5, 1, 2};

    Solution sol;
    auto ans = sol.findMin(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Compare mid vs hi.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Min in unsorted half.
*/
