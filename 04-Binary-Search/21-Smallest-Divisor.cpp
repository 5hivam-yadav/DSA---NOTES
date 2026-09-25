/*
Problem: Smallest Divisor
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given an array and threshold, find the smallest divisor d so that the sum of ceil(a[i]/d) is within threshold (binary search on d).
Sample Input: nums = [1, 2, 5, 9], threshold = 6
Sample Output: 5
Explanation: With d=5 the sum is 1+1+1+2 = 5 which fits 6; d=4 gives 7 which exceeds.
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
    int smallestDivisor(vector<int>& a, int t) {
        int lo = 1, hi = 1e6;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            long long s = 0;
            for (int x : a) s += (x + m - 1) / m;
            if (s <= t) hi = m;
            else lo = m + 1;
        }
        return lo;
    }
};

int main() {
    vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;

    Solution sol;
    auto ans = sol.smallestDivisor(nums, threshold);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Ceil-sum feasibility.
Time Complexity:
O(n log Max)
Space Complexity:
O(1)
Key Idea:
BS on divisor.
*/
