/*
Problem: Split Array Largest Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given an array and k, split into k subarrays minimizing the largest
sum (binary search on the answer). Sample Input: nums = [7,2,5,10,8], k = 2
Sample Output: 18
Explanation: Split [7,2,5] and [10,8] gives max sum 18.
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
    bool ok(vector<int> &a, int k, int mx) {
        int c = 1;
        long long cur = 0;
        for (int x : a) {
            if (x > mx)
                return false;
            if (cur + x > mx) {
                c++;
                cur = 0;
            }
            cur += x;
        }
        return c <= k;
    }
    int splitArray(vector<int> &a, int k) {
        int lo = *max_element(a.begin(), a.end()),
            hi = accumulate(a.begin(), a.end(), 0);
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (ok(a, k, m))
                hi = m;
            else
                lo = m + 1;
        }
        return lo;
    }
};

/*
Approach:
Same as allocate.
Time Complexity:
O(n log Sum)
Space Complexity:
O(1)
Key Idea:
Min largest piece.
*/
